#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

int GetSock(char* ip, char *port)
{
	// 1.socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("sock");
		exit(1);
	}

	// 2.bind
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = inet_addr(ip);
	local.sin_port   = htons(atoi(port));
	if(bind(sock, (struct sockaddr*)&local, sizeof(struct sockaddr_in)) < 0)
	{
		perror("bind");
		close(sock);
		exit(2);
	}

	// 3.listen
	if(listen(sock, 5) < 0)
	{
		perror("listen");
		close(sock);
		exit(3);
	}

	return sock;
}

void *handle(void *arg)
{
	int sock = *(int *)arg;
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
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Usage # %s [local_ip] [loacl_port]\n");
		return 4;
	}

	int sock = GetSock(argv[1], argv[2]);

	while(1)
	{
		struct sockaddr_in peer;
		socklen_t len = sizeof(peer);
		int peer_sock = accept(sock, (struct sockaddr*)&peer, &len);
		if(peer_sock < 0)
		{
			perror("accept");
			close(sock);
			return 5;
		}

		printf("client has connected, ip is %s; port is %d\n", inet_ntoa(peer.sin_addr), ntohs(peer.sin_port));
		// create thread
		pthread_t pid;
		int ret = pthread_create(&pid, NULL, handle, &peer_sock);
		if(ret != 0)
		{
			perror("pthread_create");
			close(sock);
			return 6;
		}
		pthread_detach(pid);
	}

	close(sock);
	return 0;
}
