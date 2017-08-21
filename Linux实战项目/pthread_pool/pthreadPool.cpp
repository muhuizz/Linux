#include "pthreadPool.h"
using namespace std;
/*
 *  bool _isRunning; 
 *  int _threadNum; 
 *  pthread_t* _pthread; 
 *  std::queue<Task> _taskQueue; 
 *  pthread_mutex_t _mutex; 
 *   pthread_cond_t _cond;
 * */

ThreadPool::ThreadPool(int num)
	:_threadNum(num)
{}

ThreadPool::~ThreadPool()
{
	Stop();
}

void ThreadPool::Start()
{
	_creatThreads();
	_isRunning = true;
}

size_t ThreadPool::AddTask(Task* t)
{
	pthread_mutex_lock(&_mutex);
	_taskQueue.push(t);
	int size = _taskQueue.size();
	pthread_mutex_unlock(&_mutex);
	pthread_cond_signal(&_cond);
	return size;
}
int ThreadPool::Size()
{
	pthread_mutex_lock(&_mutex);
	int size = _taskQueue.size();
	pthread_mutex_unlock(&_mutex);
	return size;
}


//******************************************************

void* ThreadPool::thread_func(void* arg) // static
{
	ThreadPool* pool = (ThreadPool*)arg;
	while(pool->_isRunning)
	{
		Task* task = pool->takeTask();
		if(task == NULL)
		{
			cout<<"thread pool is stop..."<<endl;
			return NULL;
		}
		task->run();
		delete task;
	}
	return NULL;
}

int ThreadPool::_creatThreads()
{
	pthread_mutex_init(&_mutex, NULL);
	pthread_cond_init(&_cond,NULL);
	_threads = new pthread_t[_threadNum];
	for(int i = 0; i < _threadNum; i++)
	{
		pthread_create(&_threads[i], NULL, thread_func, this);
	}
	return 0;
}

Task* ThreadPool::takeTask()
{
	Task* task= NULL;
	while(!task)
	{
		pthread_mutex_lock(&_mutex);
		while(_taskQueue.empty() && _isRunning)
		{
			pthread_cond_wait(&_cond, &_mutex);
		}
		if(!_isRunning)
		{
			pthread_mutex_unlock(&_mutex);
			break;
		}
		else if(_taskQueue.empty())
		{
			pthread_mutex_unlock(&_mutex);
			continue;
		}

		task = _taskQueue.front();
		_taskQueue.pop();
		pthread_mutex_unlock(&_mutex);
	}
	return task;
}

void ThreadPool::Stop()
{
	if(!_isRunning)	
		return;
	// _isRunning is set to faluse only here
	_isRunning = false;
	pthread_cond_broadcast(&_cond);
	for(size_t i = 0; i < _threadNum; i++)
	{
		pthread_join(_threads[i], NULL);
	}
	delete[] _threads;
	_threads = NULL;

	pthread_mutex_destroy(&_mutex);
	pthread_cond_destroy(&_cond);
}
