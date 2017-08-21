#include "pthreadPool.h"
using namespace std;
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

class ZTask:public Task
{
public:
	ZTask(void* addr, const std::string& s)
		:Task(addr, s)
	{}
	virtual int run()
	{
		int sock = atoi(_taskname.c_str());
		cout<<"***************  "<<sock<<endl;
		while(1)
		{
			char buf[1024];
			memset(buf, 0, sizeof(buf));
			ssize_t _s = read(sock, buf,sizeof(buf));
			if(_s > 0)
			{
				buf[_s] = 0;
				printf("Recv# %s\n", buf);
			}
			else if(_s == 0)
			{
				printf("client quit!\n");
				break;
			}
			else
			{
				perror("read error");
				break;
			}
		}
		close(sock);
		return 0;	
	}
};
int startup(const char* _ip, int _port)
{
	int local = socket(AF_INET, SOCK_STREAM, 0);
	if(local < 0)
	{
		perror("socket");
		exit(2);
	}
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = ntohs(_port);
	server.sin_addr.s_addr = inet_addr(_ip);
	if(bind(local, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		perror("bind");
		close(local);
		exit(3);
	}
	if(listen(local, 5)< 0)
	{
		perror("listen");
		exit(4);
	}
	return local;
}

int main(int argc, const char* argv[])
{
	if(argc != 3)
	{
		cout<<"Usage()"<<endl;
		return 1;
	}
	int listen_sock = startup(argv[1], atoi(argv[2]));
	
	int opt = 1;
	setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	
	ThreadPool pool(20);
	pool.Start();
	while(1)
	{
		struct sockaddr_in peer;
		socklen_t len = sizeof(struct sockaddr_in);
		int remote = accept(listen_sock, (struct sockaddr*)&peer, &len);
		if(remote < 0)
		{
			perror("accept");
			close(listen_sock);
			return 5;
		}
		printf("client has connected, ip is %s; port is %d\n", inet_ntoa(peer.sin_addr), ntohs(peer.sin_port));
		// pool
		char name[10];
		sprintf(name, "%d", remote);
		ZTask *t = new ZTask((void*)&peer, string(name));
		//ZTask t((void*)&peer, string(name));
		pool.AddTask(t);
	}
	close(listen_sock);

	return 0;
}
