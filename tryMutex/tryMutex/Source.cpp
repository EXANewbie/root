#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

using namespace std;


queue<int> que;
mutex mtx;
const int MAX_COUNT = 999;

void dequeue(int myid)
{
	int t = 10;
	while (t--)
	{
		mtx.lock();
		if (!que.empty())
		{
			int object = que.front();
			que.pop();
			cout << "consumer " << myid << " : " << object << endl;
		}
		
		mtx.unlock();
		
	}
}


void enqueue(int element)
{
	mtx.lock();
	que.push(element);
	mtx.unlock();
	//
}
bool is_full() {
	return que.size() >= MAX_COUNT;
}
void Producer_run(/*SYNCHED_QUEUE *queue, */int index) {
	srand(time(NULL));

	int t = 10;
	while (t--) {
//		queue.push_waited();

		if (/*queue->*/is_full() == false) {
			int element = rand() % 100;
			/*queue->*/enqueue(element);
//			Sleep(500 * (index + 1));
			cout << "Producer " << index << " push " << element << endl;
		}

	}
}
	
int main() {
	int p, c;
	cout << "input producer : ";
	cin >> p;

	
	cout << "input consumer : ";
	cin >> c;
	
	vector<thread> vt;
	
	for (int i = 0; i < c; ++i)
	{
		vt.push_back(thread(dequeue, i));
	}

	vector<thread> vec;

	for (int i = 0; i < p; i++) {
		vec.push_back(thread(Producer_run, i));
		
	}

	for (int i = 0; i < p; i++) {
		vec[i].join();
		vt[i].join();
	}

	cout << "end" << endl;
	vec.clear();

}
