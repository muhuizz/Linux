#include "httpd.h"

#include <time.h>
static void usage(const char *msg)
{
	printf("Usage# %s [local_ip] [local_port]\n", msg);
	print_log("Invalid arguments", FATAL);
}

static int startup(const char *_ip, int _port)
{
	assert(_ip);
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		print_log("socket error", FATAL);
		exit(2);
	}
	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port   = htons(_port);
	local.sin_addr.s_addr = inet_addr(_ip);
	if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
	{
		print_log("bind error", FATAL);
		exit(3);
	}
	if(listen(sock, 5) < 0)
	{
		print_log("listen error", FATAL);
		exit(4);
	}
	return sock;
}

static void* fun_client(void * arg)
{
	assert(arg);
	int sock = (int)arg;
	pthread_detach(pthread_self());
	handle_client(sock);
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}

	int listen_sock = startup(argv[1],atoi( argv[2]));

	// printf("listen_sock is ready!\n");
	while(1)
	{
		struct sockaddr_in peer;
		socklen_t len  =sizeof(peer);
		int client = accept(listen_sock, (struct sockaddr*)&peer, &len);
		if( client  < 0 )
		{
			print_log("accept error", FATAL);
			continue;
		}
		printf("accept success# %s : %d!\n", inet_ntoa(peer.sin_addr), ntohs(peer.sin_port));
		pthread_t pid;
		if(pthread_create(&pid, NULL, fun_client, (void*)client) != 0)// pthread_create faild
		{
			print_log("pthread_create error", FATAL);	
			close(client);
		}
	}
	close(listen_sock);
	return 0;
}
