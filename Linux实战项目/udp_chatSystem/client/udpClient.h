#ifndef _UDPClient_HPP__
#define _UDPClient_HPP__

#include <iostream>
#include <string>
#include <map>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include "log.h"
#include "dataPool.h"
#define SIZE 1024

class Client
{
	public:
		Client(const std::string& ip, const int& post);
		void InitClient();
		int RecvData(string& recv_str);
		int SendData(const std::string& send_str, const struct sockaddr_in dest);
		~Client();
	private:
		Client(const Client& svr);
	protected:
		int sock;
		std::string server_ip;
		int server_port;
};

#endif// _UDPClient_HPP__
