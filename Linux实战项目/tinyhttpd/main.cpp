#include "httpd.h"

#include <time.h>
static void usage(const char *msg)
{
	printf("Usage# %s [local_ip] [local_port]\n", msg);
	print_log("Invalid arguments!", FATAL);
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}

	int listen_sock = startup(argv[1],atoi( argv[2]));

	int opt = 1;
	setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	daemon(1, 0);
	
	ThreadPool pool;
	pool.Start();
	while(1)
	{
		char buf[SIZE];
		struct sockaddr_in peer;
		socklen_t len  =sizeof(peer);
		int client = accept(listen_sock, (struct sockaddr *)&peer, &len);
		if( client  < 0 )
		{
			print_log("accept error", FATAL);
			continue;
		}
		sprintf(buf, "accept success# %s : %d!\n", inet_ntoa(peer.sin_addr), ntohs(peer.sin_port));
		print_log(buf, NORMAL);
		char name[10];
		sprintf(name, "%d", client);
		ZTask* pt = new ZTask((void*)&peer, std::string(name));
		pool.AddTask(pt);

	}
	close(listen_sock);
	return 0;
}
