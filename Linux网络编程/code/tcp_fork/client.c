#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
	// check Input
	if(argc != 3)
	{
		printf("Invalid Input!\n");
		printf("Usage# %s [ip] [port]\n");
		return 1;
	}
	
	// create socket
	int client_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(client_sock < 0)
	{
		perror("socket error");
		exit(1);	
	}
	// connect
	struct sockaddr_in server_socket;
	struct sockaddr_in client_socket;

	server_socket.sin_family      = AF_INET;
	server_socket.sin_port        = htons(atoi(argv[2]));
	server_socket.sin_addr.s_addr = inet_addr(argv[1]);
	int ret = connect(client_sock, (struct sockaddr *)&server_socket, sizeof(struct sockaddr_in));
	if(ret < 0)
	{
		perror("connect error");
		printf("*****************8");
		close(client_sock);
		return 4;
	}
	printf("connect success!\n");
	int len = sizeof(struct sockaddr_in);
	char buf_ip[100];
	memset(buf_ip, 0, sizeof(buf_ip));
	getsockname(client_sock, (struct sockaddr *)&client_socket, &len);
	inet_ntop(AF_INET, &client_socket.sin_addr, buf_ip, sizeof(buf_ip));
	printf("I'm client, my IP addr is %s, my port is %d\n", \
			buf_ip, ntohs(client_socket.sin_port));
	// send
	while(1)
	{
		printf("Send# ");
		fflush(stdout);
		char buf[1024];
		memset(buf, 0, sizeof(buf));
		ssize_t _s  = read(0, buf, sizeof(buf));
		printf("*************************\n");
		if(_s < 0)
		{
			perror("read error");
			close(client_sock);
			return 5;
		}
		write(client_sock ,buf, _s);
		memset(buf, 0, sizeof(buf));
	}

	close(client_sock);
	return 0;
}
