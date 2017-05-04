#include "udpClient.h"
#include "dataType.h"
#include "window.h"

using namespace std;

Window win;
string nick_name;
string school;
datatype recv_data;
datatype send_data;
Client* cli_sig = NULL;


void Usage(const char* server)
{
	cout<<"Usage: "<< server <<"[server_ip] [server_port]"<<endl;
}

void* header_fun(void *arg)
{
	pthread_detach(pthread_self());
	int index = 1;
	while(1)
	{
		win.draw_header_windows();
		int nowy = 0;
		int nowx = 0;
		getmaxyx(win.header, nowy, nowx);
		string msg = "Welcome to ChatingSystem^-^";
		
		win.send_msg_to_window(win.header, nowy/2-1, index++, msg);
		index%=(COLS-msg.size());
		if(index == 0)
			index = 1;
		usleep(300000);
	}
	return NULL;
}

void* output_fun(void *arg)
{
	pthread_detach(pthread_self());
	Client *cli = (Client*)arg;
	win.draw_output_windows();
	win.draw_friend_list_windows();
	
	int index = 1 ;
	string recv_msg;
	
	int x = 0;
	int y = 0;
	getmaxyx(win.output, y, x);
	
	while(1)
	{
		string recvStr;
		string _friend;
		cli->RecvData(recvStr);
		
		recv_data.stringToValue(recvStr);

		recv_msg.clear();	
		recv_msg += recv_data.nick_name;
		recv_msg += "@";
		recv_msg += recv_data.school;
		
		_friend = recv_msg;
		if(recv_data.cmd == "QUIT")
		{
			cli->DelUser(_friend);
		}
		else
		{
			cli->AddUser(_friend);
			recv_msg += "# ";
			recv_msg += recv_data.msg;
			
			index %= (y-1);
			if(index == 0)
			{
				win.clear_lines(win.output, 1, y-2);
				win.draw_output_windows();
				index = 1;
			}
			win.send_msg_to_window(win.output, index++, 1, recv_msg);
		}
		
		set<string>::iterator iter = (cli->friend_online).begin();
		int j = 1;
		win.clear_lines(win.friend_list, 1, y-2);
		win.draw_friend_list_windows();
		while(iter != (cli->friend_online).end())
		{
			win.send_msg_to_window(win.friend_list, j++, 1, *iter);
			iter++;
		}
	}
	return NULL;
}

void* input_fun(void* arg)
{
	pthread_detach(pthread_self());
	Client *cli = (Client*)arg;
	send_data.nick_name = nick_name;
	send_data.school = school;
	int index = 0;
	while(1)
	{
		std::string buf;
		win.draw_input_windows();
		keypad(win.input, true);
		win.send_msg_to_window(win.input, 1, 1, "Please Input# ");
		win.recv_msg_from_window(win.input, buf, 1024);

		send_data.msg = buf;
		send_data.cmd = "None";

		string sendStr;
		send_data.valueToString(sendStr);
		cli->SendData(sendStr);
	}
	return NULL;
}

void fun_int(int)
{
	send_data.nick_name = nick_name;
	send_data.school = school;
	send_data.msg = "";
	send_data.cmd = "QUIT";
	string sendStr;
	send_data.valueToString(sendStr);
	cli_sig->SendData(sendStr);
	exit(1);
}

int main(int argc, char *argv[])
{
	if(argc != 5)
	{
		Usage(argv[0]);
		exit(1);
	}

	string _ip = argv[1];
	int _port = atoi(argv[2]);
	nick_name = argv[3];
	school = argv[4];

	Client cli(_ip, _port);
	cli.InitClient();
	cli_sig = &cli;
	
	signal(SIGINT, fun_int);


	pthread_t header_pthread;
	pthread_t output_pthread;
	pthread_t input_pthread;

	pthread_create(&header_pthread, NULL, header_fun, NULL);
	pthread_create(&output_pthread, NULL, output_fun, &cli);
	pthread_create(&input_pthread, NULL, input_fun, &cli);
	
	while(1);
	return 0;
}
//void* sendToNet(void *arg)
//{
//	Client *cli = (Client*)arg;
//	while(1)
//	{
//		datatype d;
//		d.nick_name = "lzk";
//		d.school = "PK-University";
//		d.msg = "NetWork";
//		d.cmd = "1234";
//		string sendStr;
//		d.valueToString(sendStr);
//		cli->SendData(sendStr);
//		cout<<"client Send# "<<sendStr<<endl;
//		sleep(1);
//	}
//	return NULL;
//}
//void* getFromNet(void *arg)
//{
//	Client *cli = (Client*)arg;
//	while(1)
//	{
//		string recvStr;
//		cli->RecvData(recvStr);
//		cout<<"client Recv# "<<endl;
//		//cout<<recvStr<<endl;
//		datatype d;
//		d.stringToValue(recvStr);
//		cout<<d.nick_name<<"-"<<d.school<<":"<<d.msg<<endl;
//	}
//	return NULL;
//}
//
//int main(int argc, char *argv[])
//{
//	if(argc != 3)
//	{
//		Usage(argv[0]);
//		exit(1);
//	}
//
//	string _ip = argv[1];
//	int _port = atoi(argv[2]);
//	Client cli(_ip, _port);
//	cli.InitClient();
//	
//	pthread_t pth1;
//	pthread_t pth2;
//	pthread_create(&pth1, NULL, sendToNet, &cli);
//	pthread_create(&pth2, NULL, getFromNet, &cli);
//	pthread_join(pth1, NULL);
//	pthread_join(pth2, NULL);
//
//	return 0;
//}
