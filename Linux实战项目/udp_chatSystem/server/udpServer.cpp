#include "udpServer.h"
using namespace std;

Server::Server(const string& _ip, const int& _port)
	:ip(_ip)
	 ,port(_port)
	 ,data(128)
{}

void Server::InitServer()
{
	sock=socket(AF_INET, SOCK_DGRAM, 0);
	if(sock < 0)
	{
		print_log("create sock failed", FATAL);
		exit(1);
	}
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip.c_str());
	if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
	{
		print_log("bind sock failed", FATAL);
		exit(2);
	}
}

void Server::AddUser(const struct sockaddr_in remote)
{
	user_list[remote.sin_addr.s_addr] = remote;
}

int Server::RecvData(string& recv_str)
{
	char buf[SIZE];
	struct sockaddr_in remote;
	socklen_t len = sizeof(remote);
	ssize_t _s = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&remote, &len);
	if(_s >= 0)
	{
		recv_str = buf;
		AddUser(remote);
		data.PutData(recv_str);
	}
	return _s;
}

int Server::SendData(const struct sockaddr_in remote, const string& send_str)
{
	size_t _s = sendto(sock, send_str.c_str(), send_str.size(), 0, (struct sockaddr*)&remote, sizeof(remote));
	return _s;
}

void Server::Broadcast()
{
	string send_str;
	data.GetData(send_str);
	map<in_addr_t, struct sockaddr_in>::iterator iter = user_list.begin();
	while(iter != user_list.end())
	{
		SendData(iter->second, send_str);
		iter++;
	}
}

Server::~Server()
{
	close(sock);
	port = 0;
}
