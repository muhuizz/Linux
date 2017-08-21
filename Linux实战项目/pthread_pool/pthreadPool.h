#ifndef __PTHREADPOOL_H__
#define __PTHREADPOOL_H__

#include <iostream>
#include <string>
#include <pthread.h>
#include <queue>
#include <list>
#define NUM_THREAD 10
class Task
{
public:
	Task(void* arg = NULL, const std::string& name="")
		:_arg(arg)
		 ,_taskname(name)
	{}
	virtual ~Task()
	{}
	void SetArg(void* arg)
	{
		_arg = arg;
	}
	virtual int run() = 0;// pure virtual function
protected:
	void* _arg;
	std::string _taskname;
};

class ThreadPool
{
public:
	ThreadPool(int num = NUM_THREAD);
	~ThreadPool();
public:
	size_t AddTask(Task* t);
	int Size();
	void Start();
protected:
	int _creatThreads();
	static void* thread_func(void* arg); // thread func
	Task* takeTask();
	void Stop();

private:
	ThreadPool& operator=(const ThreadPool&);
	ThreadPool(const ThreadPool&);
protected:
	volatile bool _isRunning;	// volatile
	int _threadNum;
	pthread_t* _threads;

	std::queue<Task*> _taskQueue;
	pthread_mutex_t _mutex;
	pthread_cond_t _cond;
};

#endif// __PTHREADPOOL_H__
