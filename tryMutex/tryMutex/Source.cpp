#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

using namespace std;

class SYNCHED_QUEUE
{
private :
	queue<int> que;
	mutex mtx;

	mutex push_enable;
	const int MAX_COUNT = 100;

public :
	SYNCHED_QUEUE() {}
	void enqueue(int element)
	{
//		mtx.lock();
		que.push(element);
//		mtx.unlock();
	}
	int dequeue()
	{
//		mtx.lock();
		int obj = que.front();
		que.pop();
//		mtx.unlock();
		return obj;
	}
	
	bool empty()
	{
		return que.empty();
	}

	bool is_full()
	{
		return que.size() >= MAX_COUNT;
	}

	void lock() {
		mtx.lock();
	}

	void unlock() {
		mtx.unlock();
	}
};

void Producer_run(SYNCHED_QUEUE* queue, int index)
{
	srand(time(NULL));

	while (true)
	{
		Sleep(500 + (rand()*index % 1000)); // 생산시간
		queue->lock();
		if (queue->is_full() == false)
		{
			int element = rand() % 100;
			queue->enqueue(element);
			cout << "Producer " << index << " push " << element << endl;
		}
		queue->unlock();
	}
}
void ConsumerRun(SYNCHED_QUEUE* que,int id)
{
	while (true)
	{
		que->lock();
		if (!(que->empty()))
		{
			int obj=que->dequeue();
			cout << "consumer " << id << " : " << obj << endl;
		}
		que->unlock();
		Sleep(500 + (rand()*id % 1000)); // 소비시간
	}
}


	
int main()
{
	int p, c;
	cout << "input producer : ";
	cin >> p;
	cout << "input consumer : ";
	cin >> c;

	SYNCHED_QUEUE que;

	vector<thread> vec_producer;
	vector<thread> vec_consumer;

	for (int i = 0; i < p; ++i)
	{
		vec_producer.push_back(thread(Producer_run, &que, i));
	}

	for (int i = 0; i < c; ++i)
	{
		vec_consumer.push_back(thread(ConsumerRun, &que, i));
	}
	
	for (int i = 0; i < p; ++i)
	{
		vec_producer[i].join();
	}

	for (int i = 0; i < c;++i)
	{
		vec_consumer[i].join();
	}

	vec_producer.clear();
	vec_consumer.clear();
}
