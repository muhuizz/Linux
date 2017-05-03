#ifndef _UDPServer_HPP__
#define _UDPServer_HPP__

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
#include "dataType.h"
#define SIZE 1024
#define DATAPOOL_SIZE 1024
class Server
{
	public:
		Server(const std::string& ip, const int& post);
		void InitServer();
		int RecvData(std::string& recvStr);
		void Broadcast();
		~Server();
	protected:
		Server(const Server& svr);
		void AddUser(const struct sockaddr_in remote);
		void DelUser(const struct sockaddr_in remote);
		int SendData(const struct sockaddr_in remote, const std::string& send_str);
	protected:
		int sock;
		std::string ip;
		int port;
		map<in_addr_t, struct sockaddr_in> user_list;	// 优化
		DataPool data;
};

#endif// _UDPServer_HPP__
