#include <string>
#include <iostream>
#include <thread>
#include <random>
#include <mutex>
using namespace std;

class print
{
 	string s;
 	mutex m;
 public:
	print(const string& s)
	{
		this->s=s;
	}
	void operator()()
	{
		lock_guard<mutex> lck(m);
		default_random_engine dre(s[0]);
		uniform_int_distribution<int> id(1,100);
		for(auto c:s)
		{
			this_thread::sleep_for(chrono::milliseconds(id(dre)));
			cout.put(c).flush();
		}
	}

};


void hello()
{
	while (true)
	{
		chrono::milliseconds timespan(1000);
		this_thread::sleep_for(timespan);
		cout<<"hello world"<<endl;
	}
}

int main()
{
	//thread t3(hello);
	thread t1(print("hello "));
	thread t2(print("Parallel World!\n"));
	
	
	t1.join();
	t2.join();
	//t3.join();
	return 0;
}


