#include <thread>
#include <mutex>
#include <memory>
#include <future>
#include <iostream>
using namespace std;

int calculate_the_answer(){
	this_thread::sleep_for(chrono::milliseconds((long long)(1000)));
	return 42;
}

int main()
{
	packaged_task<int()> pt(calculate_the_answer);
	future<int> future_answer = pt.get_future();
	thread t(move(pt));
	cout<< future_answer.get() <<endl;
	t.join();

}