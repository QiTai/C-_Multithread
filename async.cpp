#include <thread>
#include <mutex>
#include <memory>
#include <future>
#include <iostream>
using namespace std;

int calculate_the_answer(){
	this_thread::sleep_for(chrono::milliseconds((long long)(10000)));
	return 42;
}

int main()
{
	auto f=async(calculate_the_answer);
	cout<< f.get() <<endl;

}
