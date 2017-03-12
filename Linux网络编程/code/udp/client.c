#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
int main(int argc, char *argv[])	
{
	if(argc != 3){
		printf("Usage : %s [server_ip] [server_port]",argv[0]);
		return 1;
	}

	// 1.socket
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0){
		perror("socket");
		return 2;
	}
	// no connect   
 	// 2.sendto
	
	int len = sizeof(struct sockaddr_in);
	struct sockaddr_in peer;
	peer.sin_family      = AF_INET;
	peer.sin_addr.s_addr = inet_addr(argv[1]);
	peer.sin_port        = htons((atoi(argv[2])));

	while(1){
		char buf[1024];
		memset(buf, 0, sizeof(buf));
		printf("Send# ");
		fflush(stdout);
		ssize_t _s = read(0, buf, sizeof(buf));
		if(_s < 0)
		{
			perror("read");
			continue;
		}
		buf[_s-1] = 0;
		ssize_t ret = sendto(sock, buf, strlen(buf), 0,\
				(struct sockaddr*)&peer,len);

		if(ret < 0)
		{
			perror("sendto");
			continue;
		}

	}
	close(sock);
	return 0;
}
