#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

#define MAX_LEN 512
int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Usage# %s [local_ip] [local_port]", argv[0]);
		return 1;
	}
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(argv[2]));
	local.sin_addr.s_addr = inet_addr(argv[1]);
	socklen_t len = sizeof(local);
	int ret = connect(sock, (struct sockaddr*)&local, len);
	if(ret < 0)
	{
		perror("connect");
		return 2;
	}
	printf("connect success!\n");

	char buf[MAX_LEN];
	memset(buf, 0, MAX_LEN);
	while(1)
	{
		ssize_t _s = read(0,buf, MAX_LEN);
		buf[_s] =0;
		send(sock, buf, _s, 0);
		printf("client Send# %s \n", buf);
		char recv_buf[MAX_LEN];
		memset(recv_buf, 0, MAX_LEN);
		ssize_t len = recv(sock,recv_buf, MAX_LEN-1, 0);
		if(len < 0)
		{
			perror("recv");
			continue;	
		}
		printf("client recv# %s\n", recv_buf);
	}
	return 0;
}
