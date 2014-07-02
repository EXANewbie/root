#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <vector>

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
		//
	}
	void dequeue(int myid)
	{
		//
		while (1)
		{
			mtx.lock();
			if (!que.empty())
			{
				int object = que.front();
				que.pop();
				cout << "consumer "<<myid<<" : " << object << endl;
			}
			mtx.unlock();
		}
	}	
};

queue<int> que;
mutex mtx;

void dequeue(int myid)
{
	//
	while (1)
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


int main() {
	int p, c;
	cout << "input producer : ";
	cin >> p;
	
	cout << "input consumer : ";
	cin >> c;
	
	//SYNCHED_QUEUE que;
	
	vector<thread> vt;
	
	for (int i = 0; i < c; ++i)
	{
		vt.push_back(thread(dequeue, i));
	}
	for (int i = 0; i < c; ++i)
	{
		vt[i].join();
	}

	
}
