#include "udpClient.h"
#include "dataType.h"

using namespace std;


void Usage(const char* server)
{
	cout<<"Usage: "<< server <<"[server_ip] [server_port]"<<endl;
}

void* sendToNet(void *arg)
{
	Client *cli = (Client*)arg;
	while(1)
	{
		datatype d;
		d.nick_name = "lzk";
		d.school = "PK-University";
		d.msg = "NetWork";
		d.cmd = "1234";
		string sendStr;
		d.valueToString(sendStr);
		cli->SendData(sendStr);
		cout<<"client Send# "<<sendStr<<endl;
		sleep(1);
	}
	return NULL;
}
void* getFromNet(void *arg)
{
	Client *cli = (Client*)arg;
	while(1)
	{
		string recvStr;
		cli->RecvData(recvStr);
		cout<<"client Recv# "<<endl;
		//cout<<recvStr<<endl;
		datatype d;
		d.stringToValue(recvStr);
		cout<<d.nick_name<<"-"<<d.school<<":"<<d.msg<<endl;
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
	Client cli(_ip, _port);
	cli.InitClient();
	
	pthread_t pth1;
	pthread_t pth2;
	pthread_create(&pth1, NULL, sendToNet, &cli);
	pthread_create(&pth2, NULL, getFromNet, &cli);
	pthread_join(pth1, NULL);
	pthread_join(pth2, NULL);

	return 0;
}
