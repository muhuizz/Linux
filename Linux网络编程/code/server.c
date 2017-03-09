#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

void Usage(char *msg)
{
	printf("invalid Input!\n");
	printf("Usage: %s [ip] [port]\n",msg);
}

int create_socket(char *port, char *addr)
{
	// 1.create an endpoint for communication
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket error");
		exit(1);
	}
	// 
	struct sockaddr_in local;
	local.sin_family = AF_INET; 
	local.sin_port   = htons(atoi(port));
	local.sin_addr.s_addr   = inet_addr(addr);

	if(bind(sock, (struct sockaddr *)&local, sizeof(local)) < 0)
	{
		perror("bing error");
		close(sock);
		exit(2);
	}
	
	if(listen(sock, 5) < 0)
	{
		perror("listen error");
		close(sock);
		exit(3);
	}
	return sock;
}


int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		Usage(argv[0]);
		return 1;
	}
	// create socket
	int listen_sock = create_socket(argv[2], argv[1]);
	struct sockaddr_in client;
	socklen_t len = sizeof(struct sockaddr);
	while(1){
		char buf[1024];
		memset(buf, 0, sizeof(buf));

		int ret = 0;
		if((ret = accept(listen_sock, (struct sockaddr*)&client, &len)) < 0)
		{
			perror("accept error");
			continue;
		}
		while(1)
		{
			ssize_t _s = read(ret, buf, sizeof(buf)-1);
			printf("*************************\n");
			if(_s > 0)
			{
				printf("client# ");
				fflush(stdout);
				buf[_s-1] = 0;
				printf("%s\n", buf);
			}
			else if (_s == 0)
			{
				printf("client quit!\n");
				break;
			}
		}
	}



	return 0;
}
