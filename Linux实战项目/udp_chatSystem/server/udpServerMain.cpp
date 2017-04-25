#include "udpServer.h"

using namespace  std;


void Usage(const char* Server)
{
	cout<<"Usage: "<< Server <<"[local_ip] [local_port]"<<endl;
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


	return 0;
}
