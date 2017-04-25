#include "udpClient.h"
using namespace std;
Client::Client(const string& _ip, const int& _port)
	:server_ip(_ip)
	 ,server_port(_port)
{}

void Client::InitClient()
{
	sock=socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0)
	{
		print_log("create sock failed", FATAL);
		exit(1);
	}
}


int Client::RecvData(string& recv_str)
{
	char buf[SIZE];
	struct sockaddr_in remote;
	socklen_t len = sizeof(remote);
	ssize_t _s = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&remote, &len);
	if(_s >= 0)
	{
		recv_str = buf;
	}
	return _s;
}
int Client::SendData(const string& str)
{
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(server_port);
	server.sin_addr.s_addr = inet_addr(server_ip.c_str());

	size_t _s = sendto(sock, str.c_str(), str.size(), 0, (struct sockaddr*)&server, sizeof(server));
	return _s;
}

Client::~Client()
{
	close(sock);
	server_port = 0;
}
