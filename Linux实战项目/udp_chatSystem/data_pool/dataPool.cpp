#include "dataPool.h"

using namespace std;
DataPool::DataPool(int capacity = CAPACITY)
	:cap(capacity)
	 ,size(0)
	 ,product_pos(0)
	 ,consumer_pos(0)
{
	sem_init(&blank, 0, cap);
	sem_init(&data, 0, 0);
	pool.reserve(cap);
}
void DataPool::GetData(string outString)
{
	sem_wait(&data);
	outString=pool[consumer_pos];
	consumer_pos++;
	consumer_pos %= cap;
	size--;
	sem_post(&blank);
}
void DataPool::PutData(string inString)
{
	sem_wait(&blank);
	pool[product_pos]=inString;
	product_pos++;
	product_pos %= cap;
	size++;
	sem_post(&data);
}
DataPool::~DataPool()
{
	cap = 0;
	size = 0;
	product_pos = 0;
	consumer_pos = 0;
	sem_destroy(&data);
	sem_destroy(&blank);
}
