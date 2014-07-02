#include <iostream>
#include <thread>
#include <mutex>
#include <queue>

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
		//
	}
	int dequeue()
	{
		//
	}	
};

int main() {
	int p, c;
	cout << "input producer : ";
	cin >> p;
	cout << endl;
	cout << "input consumer : ";
	cin >> c;
	cout << endl;

	SYNCHED_QUEUE que;

	
}
