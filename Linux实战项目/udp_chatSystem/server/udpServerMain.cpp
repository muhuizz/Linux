#include "udpServer.h"

using namespace  std;

void Usage(const char* local)
{
	cout<<"Usage: "<< local <<"[local_ip] [local_port]"<<endl;
}
	
void *fun_recv(void* arg)
{
//	pthread_detach(pthread_self());
	Server *svr = (Server*)arg;
	string recvStr;
	while(1)
	{
		svr->RecvData(recvStr);
		cout<<recvStr<<endl;
	}
	return NULL;
}

void *fun_send(void* arg)
{
//	pthread_detach(pthread_self());
	Server *svr = (Server*)arg;
	while(1)
	{
		svr->Broadcast();
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		Usage(argv[0]);
		exit(1);
	}

	string _ip = argv[1];
	int _port = atoi(argv[2]);
	Server svr(_ip, _port);
	svr.InitServer();

	daemon(0,0);
	pthread_t recv;
	pthread_t send;

	pthread_create(&recv, NULL, fun_recv, (void*)&svr);
	pthread_create(&send, NULL, fun_send, (void*)&svr);

	pthread_join(recv, NULL);
	pthread_join(send, NULL);
	return 0;
}
