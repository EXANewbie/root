#include <iostream>
#include <thread>
#include <mutex>
#include <stack>

#include <cstdlib>
#include <ctime>

using namespace std;

// TEST CODE

stack<int> p1, p2;
mutex p1_mutex, p2_mutex;
int cnt;

void func1(int val) {
	for (int i = 0; i<1000; ++i)
	{
		if (val == 1)
		{
			p1_mutex.lock();
			p1.push(rand() % 100);
			p1_mutex.unlock();
		}
		else
		{
			p2_mutex.lock();
			p2.push(rand() % 100);
			p2_mutex.unlock();
		}
	}
}



int main() {

	srand((unsigned int)time(NULL));

	thread t1(&func1, 1);
	thread t2(&func1, 2);

	t1.join();
	t2.join();

	for (int i = 0; i<1000; i++) {
		p1_mutex.lock();
		p2_mutex.lock();
		p2_mutex.lock();
		p2_mutex.lock();
		if (p1.empty() == 0 && p2.empty() == 0){
			cout << ++cnt << ": ";
			int a, b;
			a = p1.top();
			p1.pop();
			cout << "getP1 ";
			b = p2.top();
			p2.pop();
			cout << "getP2 ";
			cout << "A구입:" << a << " " << "B구입:" << b << " Total : " << a + b << endl;
		}
		p1_mutex.unlock();
		p2_mutex.unlock();
	}

	//t1.join();
	//t2.join();



	return 0;
}
