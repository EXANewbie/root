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

//	mutex push_enabled;

	const int MAX_COUNT = 10;
public :
	SYNCHED_QUEUE() {}
	void enqueue(int element)
	{
		mtx.lock();
		que.push(element);
		mtx.unlock();
		//
	}
	int dequeue()
	{
		//
	}
	//void push_waited() {
	//	mtx.lock();
	//	push_enabled.lock();
	//	mtx.unlock();
	//}

	bool is_full() {
		return que.size() < MAX_COUNT;
	}
};

void Producer_run(SYNCHED_QUEUE* queue, int index) {
	srand(time(NULL));

	while (true) {
//		queue.push_waited();

		if (queue->is_full() == false) {
			int element = rand() % 100;
			queue->enqueue(element);
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

	SYNCHED_QUEUE que;

	vector<thread> vec_producer;
	//thread **list = new thread *[p];

	for (int i = 0; i < p; i++) {
		vec_producer.push_back(thread(Producer_run, &que, i));
		//list[i] = new thread(Producer_run, que, i+1);
	}

	// consumer


	for (int i = 0; i < p; i++) {
		vec_producer[i].join();
		//list[i]->join();
	}

	vec_producer.clear();

/*	for (int i = 0; i < p; i++) {
			delete(list[i]);
	}*/
//	delete(que);
//	delete(list);
}
