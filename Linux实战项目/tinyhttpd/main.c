#include "httpd.h"

#include <time.h>
static void usage(const char *msg)
{
	printf("Usage# %s [local_ip] [local_port]\n", msg);
	print_log("Invalid arguments", FATAL);
}


static void* fun_client(void * arg)
{
	assert(arg);
	int sock = *(int*)arg;
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

	daemon(1, 0);
	// printf("listen_sock is ready!\n");
	while(1)
	{
		char buf[SIZE];
		struct sockaddr_in peer;
		socklen_t len  =sizeof(peer);
		int client = accept(listen_sock, (struct sockaddr*)&peer, &len);
		if( client  < 0 )
		{
			print_log("accept error", FATAL);
			continue;
		}
		sprintf(buf, "accept success# %s : %d!\n", inet_ntoa(peer.sin_addr), ntohs(peer.sin_port));
		print_log(buf, NORMAL);

		pthread_t pid;
		if(pthread_create(&pid, NULL, fun_client, (void*)&client) != 0)// pthread_create faild
		{
			print_log("pthread_create error", FATAL);	
			close(client);
		}
	}
	close(listen_sock);
	return 0;
}
