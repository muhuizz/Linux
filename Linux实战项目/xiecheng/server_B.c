#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX_BUF 512
int startup(const char *_ip,unsigned short _port)
{
	assert(_ip);
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		perror("socket");
		exit(2);
	}
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = inet_addr(_ip);
	local.sin_port = htons(_port);
	socklen_t len = sizeof(local);
	if(bind(sock, (struct sockaddr*)&local, len) < 0){
		perror("bind");
		exit(3);
	}

	if(listen(sock, 5) < 0){
		perror("listen");
		exit(4);
	}

	return sock;
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Usage# $s [local_ip] [local_port]\n", argv[0]);
		return 1;
	}
	int listen_sock = startup(argv[1], atoi(argv[2]));
	while(1)
	{
		int client_sock=accept(listen_sock, NULL,NULL);
		char buf[MAX_BUF];
		memset(buf, 0, MAX_BUF);
		int i =0;
		ssize_t _s = recv(client_sock, buf, MAX_BUF-1,0);
		if(_s < 0)
		{
			perror("recv");
			continue;
		}
		buf[_s] = 0;
		printf("Recv buf# %s\n", buf);
		for(i =0 ;i < _s/2; i++)
		{
			char tmp = buf[i];
			buf[i] = buf[_s-i];
			buf[_s - i] = tmp;
		}
		send(client_sock, buf, _s, 0);
		printf("Send buf# %s\n", buf);
	}
	return 0;
}
