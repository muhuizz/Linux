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
	int opt = 1;
	setsockopt(listen_sock,SOL_SOCKET,SO_REUSEADDR, &opt,sizeof(opt));
	struct sockaddr_in client_socket;
	socklen_t len = sizeof(struct sockaddr);
	while(1){
		int client_sock = 0;
		if((client_sock = accept(listen_sock, (struct sockaddr*)&client_socket, &len)) < 0)
		{
			perror("accept error");
			close(listen_sock);
		}
		printf("the client ip is %s, port is %d\n",inet_ntoa(client_socket.sin_addr), ntohs(client_socket.sin_port));
		
		pid_t id = fork();
		
		if(id < 0)
		{
			perror("fork");
			close(listen_sock);
			exit(4);

		}
		else if(id == 0)
		{
			while(1)
			{
				char buf[1024];
				memset(buf, 0, sizeof(buf));
				ssize_t _s = read(client_sock, buf, sizeof(buf)-1);
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
			close(listen_sock);
			exit(1);
			sleep(3);
		}
		else	// father
		{
			int status = 0;
			while(waitpid(-1,&status, WNOHANG) > 0);
			
		}
	}

	close(listen_sock);
	return 0;
}
