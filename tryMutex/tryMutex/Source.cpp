#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class SYNCHED_QUEUE
{
private :
	queue<int> que;
	mutex mtx;
	const int MAX_COUNT = 10;

public :
	SYNCHED_QUEUE() {}
	void enqueue(int element)
	{
		mtx.lock();
		que.push(element);
		mtx.unlock();
	}
	int dequeue()
	{
		mtx.lock();
		int obj = que.front();
		que.pop();
		mtx.unlock();
		return obj;
	}
	
	bool empty()
	{
		return que.empty();
	}
};

void ConsumerRun(SYNCHED_QUEUE* que,int id)
{
	while (1)
	{
		if (!(que->empty()))
		{
			int obj=que->dequeue();
			cout << "consumer " << id << " : " << obj << endl;
		}
	}
}

	
int main() {
	int p, c;
	cout << "input producer : ";
	cin >> p;
	cout << "input consumer : ";
	cin >> c;

	SYNCHED_QUEUE que;

	vector<thread> vec_producer;
	vector<thread> vec_consumer;

	
	for (int i = 0; i < c; ++i)
	{
		vec_consumer.push_back(thread(ConsumerRun, &que, i));
	}

	for (int i = 0; i < p; i++) {
		vec_producer[i].join();
		vec_consumer[i].join();
	}

	vec_producer.clear();


}
