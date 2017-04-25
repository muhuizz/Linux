#include "udpClient.h"

using namespace std;


void Usage(const char* server)
{
	cout<<"Usage: "<< server <<"[server_ip] [server_port]"<<endl;
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
	Client cli(_ip, _port);
	cli.InitClient();


	return 0;
}
