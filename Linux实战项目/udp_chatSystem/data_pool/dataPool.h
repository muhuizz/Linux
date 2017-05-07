#ifndef __DATAPOOL_H__
#define __DATAPOOL_H__

#include <semaphore.h>
#include <iostream>
#include <vector>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string>
#define CAPACITY 1024
using namespace std;
class DataPool
{
	public:
		DataPool(int capacity);
		void GetData(std::string& outString);
		void PutData(const std::string& inString);
		~DataPool();
	protected:
		std::vector<std::string> pool;
		int cap;
		int size;
		int product_pos;
		int consumer_pos;
		sem_t blank;
		sem_t data;
};

#endif// __DATAPOOL_H__
