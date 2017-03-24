#ifndef __DEAL_H__
#define __DEAL_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <assert.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <setjmp.h>
#include <string.h>
#define MAX_BUF 512			// buf of 
#define MAX_EVENTS 1024		// Ready queue
#define MAX_COROUTINE 1024  // RBTree max node


typedef int(FUNC)(void *);	// 

static const char *g_server_ip, *g_A_ip, *g_B_ip;
static unsigned short g_server_port, g_A_port, g_B_port;
static int epoll_fd;

typedef struct context
{
	int _start;
	jmp_buf _env;	// last saved stack and  register info
	int _fd;		// file disc
	char _buf[MAX_BUF];
	int _lenData;	// 
}context_t, *context_p;

int accepted_sock[MAX_EVENTS];	// accepted socket id
context_t context_poll[MAX_COROUTINE];	//	


int Routine(void * ptr);
int Go(FUNC* Routine, int fd);

void RecvRequest(int fd);

void SendToA(int fd);
void RecvFromA(int fd);
void SendToB(int fd);
void RecvFromB(int fd);

void SendResponse(int fd);

void Schedule(int fd);

#endif// __DEAL_H__
