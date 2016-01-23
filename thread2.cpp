#include <thread>
#include <vector>
#include <memory>
#include <iostream>
using namespace std;           

class ThreadGroup
{
private:
	typedef unique_ptr<thread> thread_ptr;
	vector<thread_ptr> threads;

public:
	ThreadGroup(){
	}

	void run(int n, function<void(int)> f)
	{
		for(int i=0;i<n;i++)
		{
			chrono::milliseconds time(100);
			this_thread::sleep_for(time);
			threads.push_back(thread_ptr(new thread(f,i)));
		}
	}

	void join()
	{
		for(auto& pt: threads)
			pt->join();
	}
};

//void print(int n)
//{
//	while(true)
//	{
//		chrono::milliseconds time(n*1000+1000);
//		this_thread::sleep_for(time);
//		cout<<n<<"hello"<<"\n"<<endl;
//	}
//}

class ParallelSum
{
	static const int NTHREADS = 4;
	vector<int> data;
	vector<int> results;
public:
	ParallelSum() : results(NTHREADS)
	{
		for(int i=0;i<1000;i++)
			data.push_back(i+1);
	}

	void sum_task(int tid)
	{
		double ss = data.size() / NTHREADS;
		int begin = ss * tid + 0.5;
		int end = ss * (tid + 1 ) + 0.5;
		results[tid] = 0;
		for(int i = begin; i < end ; ++i)
			results[tid] += data[i];
	}

	int do_sum(){
		ThreadGroup tg;
		tg.run(NTHREADS,bind(&ParallelSum::sum_task,this,placeholders::_1));
		tg.join();

		int sum=0;
		for(auto r: results)
			sum+=r;
		cout<<sum<<endl;
		return sum;
	}

};


int main()
{
	ParallelSum *Pa=new ParallelSum();
	Pa->do_sum();

	return 0;
}
