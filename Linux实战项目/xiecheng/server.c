#include "deal.h"



int startup(const char *_ip,unsigned short _port)
{
	assert(_ip);
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		perror("socket");
		exit(2);
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = inet_addr(_ip);
	local.sin_port = htons(_port);
	socklen_t len = sizeof(local);
	if(bind(sock, (struct sockaddr*)&local, len) < 0){
		perror("bind");
		exit(3);
	}

	if(listen(sock, 5) < 0){
		perror("listen");
		exit(4);
	}

	return sock;
}

// alloc
//context_p  alloc_context(int fd)
//{
//	context_p ret = (context_p)malloc(sizeof(context_t));
//	if(ret == NULL)
//	{
//		perror("malloc");
//		exit(6);
//	}
//	ret->_fd = fd;
//	return ret;
//}
////free
//void delete_ptr(context_p ct)
//{
//	if(ct != NULL)
//	{
//		free(ct);
//	}
//}
int Register_event(int fd, int event)
{
	struct epoll_event _ev; 
	_ev.events = event;
	_ev.data.fd = fd;

	return epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &_ev);
}

// li yong chu shi hua lie init  ip he port
void  init_params(char *argv[])
{
	g_server_ip = argv[1];
	g_A_ip = argv[3];
	g_B_ip = argv[5];

	g_server_port = htons(atoi(argv[2]));
	g_A_port = htons(atoi(argv[4]));
	g_B_port = htons(atoi(argv[6]));
}



int main(int argc, char *argv[])
{
	if(argc != 7)
	{
		fprintf(stderr,"Usage# [local_ip] [local_port] [server_A_ip] [server_A_port] [server_B_ip] [server_B_port]\n");
		return 1;
	}

	init_params(argv);
	// init ip  and port
	int listen_sock = startup(g_server_ip, g_server_port);

	epoll_fd = epoll_create(MAX_COROUTINE);
	if(epoll_fd < 0)
	{
		perror("epoll_create");
		return 5;
	}
	if(Register_event(listen_sock,EPOLLIN|EPOLLET) < 0)
	{
		perror("epoll_ctl:listen_sock");
		return 6;
	}

	while(1)
	{
		struct epoll_event evs[MAX_EVENTS];
		
		int nfds = epoll_wait(epoll_fd, evs, MAX_EVENTS, -1);	//block 
		int i = 0;
		for(; i < nfds; ++i)
		{
			if((evs[i].events & EPOLLIN) && (evs[i].data.fd == listen_sock))				
			{
				struct sockaddr_in peer;
				socklen_t len = sizeof(peer);
				int client_sock = accept(listen_sock, (struct sockaddr*)&peer, &len);
				if(client_sock < 0)
				{
					perror("accept");
					continue;
				}

				Register_event(client_sock, EPOLLIN|EPOLLET);
				accepted_sock[client_sock] = client_sock;
				memset(&context_poll[client_sock], 0, sizeof(context_t));
			}//fi
			else
			{
				Go(Routine, evs[i].data.fd); // deal with
			}
		}
	}
	return 0;
}

