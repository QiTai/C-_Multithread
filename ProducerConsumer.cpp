#include <queue>
#include <condition_variable>
#include <mutex>
#include <iostream>
#include <thread>
using namespace std;



struct Message{
	string s;
	Message(const string& s):s(s){}
};
queue<Message> mqueue;
condition_variable mcond;
mutex mmutex;

ostream& operator<<(ostream& os, const Message& m){
	os<<m.s<<endl;
	return os;
}

void consumer(){
	while(true){
		unique_lock<mutex> lck(mmutex);
		mcond.wait(lck);
		cout<<"hello_answer"<<endl;
	}
}

void producer(){
	static int i;
	while(true)
	{
		unique_lock<mutex> lck(mmutex);
		chrono::milliseconds time(1000);
		this_thread::sleep_for(time);
		cout<<"hello_question"<<endl;
		mcond.notify_all();
	}
}

int main()
{
	thread t1(producer);
	thread t2(consumer);
	t1.join();
	t2.join();

	return 0;
}
