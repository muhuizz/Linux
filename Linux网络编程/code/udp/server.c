#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

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

	//2.bind
	struct sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_addr.s_addr   = inet_addr(argv[1]);
	peer.sin_port   = htons(atoi(argv[2]));

	if( bind(sock, (struct sockaddr*)&peer,\
				sizeof(struct sockaddr_in) ) < 0 )
	{
		perror("bind");
		close(sock);
		return 3;
	}
	
	// no listen; no accept.   
 	// 3.recvfrom
	
	while(1){
		char buf[1024];
		
		int len = sizeof(struct sockaddr_in);

		ssize_t _s = recvfrom(sock, buf, sizeof(buf), 0,\
				(struct sockaddr*)&peer, &len);
	

		if(_s == 0){
			printf("client is quit\n");	// you cuo 
		}
		else if(_s < 0)
		{
			perror("recvfrom");
			continue;
		}
		else
		{
				printf("the peer ip is %s, port is %d\n",\
						inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
				buf[_s-1] = 0;
				printf("client#  %s\n",buf);
				printf("-------------------------------------------\n");
		}
	}
	close(sock);
	return 0;
}
