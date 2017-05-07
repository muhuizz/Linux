#ifndef _UDPClient_HPP__
#define _UDPClient_HPP__

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include <signal.h>
#include "log.h"
#include <algorithm>
#include <set>
#define SIZE 1024

class Client
{
	public:
		Client(const std::string& ip, const int& post);
		void InitClient();
		int RecvData(std::string& recv_str);
		int SendData(const std::string& send_str);
		void AddUser(const std::string& _friend);
		void DelUser(const std::string& _friend);
		~Client();
		std::set<std::string> friend_online;
	private:
		Client(const Client& svr);
	protected:
		int sock;
		std::string server_ip;
		int server_port;
};

#endif// _UDPClient_HPP__
