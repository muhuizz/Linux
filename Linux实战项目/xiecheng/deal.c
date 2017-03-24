#include "deal.h"


// judge the fd is which
int Go(FUNC* Routine, int fd)
{
	// char stack_down[1024*1024];
	int conn_fd = accepted_sock[fd];
	context_p pc = &context_poll[conn_fd];
	if(pc->_start == 0) // new events
	{
		if(setjmp(pc->_env) == 0)
		{
			printf("this is a new routine# %d\n",conn_fd);
			Routine((void*)conn_fd);
		}
	}
	else	// awaken up routine
	{
		printf("Wake up routine# %d\n", conn_fd);
		Schedule(conn_fd);
	}
	return 0;
}

// exe-flow
int Routine(void * ptr)
{
	// char stack_down[1024*1024];
	int fd = (int)ptr;
	context_p pc = &context_poll[fd];
	printf("routine of [%d]  is start\n", fd);
	
	pc->_start = 1;
	RecvRequest(fd);
	
	SendToA(fd);
	Schedule(fd);
	RecvFromA(fd);

	SendToB(fd);
	Schedule(fd);
	RecvFromB(fd);
	
	SendResponse(fd);
	pc->_start = 0;
	
	printf("routine of [%d]  is end\n", fd);
	return 0;
}

void SendToA(int fd)
{
	context_p pc = &context_poll[fd];

	int sock = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(g_A_port);
	local.sin_addr.s_addr = inet_addr(g_A_ip);
	int len = sizeof(local);
	if(connect(sock,(struct sockaddr*)&local, len) < 0)
	{
		perror("connect");
		exit(9);
	}
	send(sock, pc->_buf, pc->_lenData, 0);
	Register_event(sock,EPOLLIN | EPOLLET);
	pc->_fd = sock;
	accepted_sock[sock]=fd;
}
void RecvFromA(int fd)
{
	context_p pc = &context_poll[fd];
	pc->_lenData = recv(pc->_fd, pc->_buf, MAX_BUF, 0);
	if(pc->_lenData < 0)
	{
		perror("recv");
		exit(10);
	}
	pc->_buf[pc->_lenData]=0;
	printf("Recv from server_A# fd is %d, buf is %s\n", pc->_fd, pc->_buf);

}
void SendToB(int fd)
{

	context_p pc = &context_poll[fd];

	int sock = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(g_B_port);
	local.sin_addr.s_addr = inet_addr(g_B_ip);
	int len = sizeof(local);
	if(connect(sock,(struct sockaddr*)&local, len) < 0)
	{
		perror("connect");
		exit(9);
	}
	send(sock, pc->_buf, pc->_lenData, 0);
	Register_event(sock,EPOLLIN | EPOLLET);
	pc->_fd = sock;
	accepted_sock[sock]=fd;
}
void RecvFromB(int fd)
{
	context_p pc = &context_poll[fd];
	pc->_lenData = recv(pc->_fd, pc->_buf, MAX_BUF, 0);
	if(pc->_lenData < 0)
	{
		perror("recv");
		exit(10);
	}
	pc->_buf[pc->_lenData]=0;
	printf("Recv from server_B# fd is %d, buf is %s\n", pc->_fd, pc->_buf);
}

void Schedule(int fd)
{
	context_p pc = &context_poll[fd];
	jmp_buf last_env;
	memcpy(last_env, pc->_env, sizeof(jmp_buf));

	if(setjmp(last_env) == 0)
	{
		printf("routine# %d,Schedule : save the context\n", fd);
		longjmp(last_env, 1);
	}

	printf("routine# %d, Schedule : contextresumed\n", fd);
}


void  RecvRequest(int fd)
{
	context_p pc = &context_poll[fd];
	pc->_lenData = recv(fd, pc->_buf, MAX_BUF-1, 0); 
	if(pc->_lenData < 0)
	{
		perror("recv");
		exit(8);
	}
	else if(pc->_lenData == 0)
	{
		printf("client is quit,routine# %d\n", fd);
		close(fd);
		jmp_buf tmp;
		memcpy(tmp, pc->_env,sizeof(jmp_buf));
		memset(pc, 0, sizeof(context_t));

		longjmp(tmp, 1);
		return;
	}
	else
	{
		pc->_buf[pc->_lenData] = 0;
	}
}

void SendResponse(int fd)
{
	context_p pc = &context_poll[fd];
	send(fd, pc->_buf, pc->_lenData, 0);

	printf("routine# %d, send response, msg = %s\n", fd, pc->_buf);
}
