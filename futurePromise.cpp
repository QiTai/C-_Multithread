#include <thread>
#include <mutex>
#include <memory>
#include <future>
#include <iostream>
using namespace std;


struct DeepThought{
	unique_ptr<thread> tp;
	promise<int> the_answer_to_life_the_universe_and_everything;
	future<int> fut;

	void future_answer()
	{
		//int x=the_answer_to_life_the_universe_and_everything.get_future().get();
		//如果上面注释的这句话就会出错！
		int x=fut.get();
		cout<<x<<endl;
	}

	void calculate()
	{
		this_thread::sleep_for(chrono::milliseconds(1000));
		fut=the_answer_to_life_the_universe_and_everything.get_future();
		the_answer_to_life_the_universe_and_everything.set_value(42);
	}
	/*void run()
	{
		tp.reset(new thread(&DeepThought::calculate,this));
	}*/
	void get()
	{
		tp.reset(new thread(&DeepThought::future_answer,this));
	}
	void join()
	{
		tp->join();
	}
};

int main()
{
	DeepThought deep_thought;
	//calculate()必须作为主线程，如果把caculate作为副线程，则报错。
	deep_thought.calculate();
	deep_thought.get();
	deep_thought.join();
}
