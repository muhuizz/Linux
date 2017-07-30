#ifndef _HTTPD_H_
#define _HTTPD_H_

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
//#include <string>
#include <sys/sendfile.h>
#include "ThreadPool/pthreadPool.h"

#define NORMAL 0
#define WARNING 1
#define FATAL 2

#define SIZE 4096

class ZTask:public Task
{
public:
	ZTask(void* addr, const std::string& s)
		:Task(addr, s)
	{}
	virtual int run();
};

int handle_client(int sock);
void print_log(const char* msg, int type);
int startup(const char *_ip, int _port);

#endif// _HTTPD_H_
