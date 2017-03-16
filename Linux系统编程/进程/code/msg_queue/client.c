#include "comm.h"

int main()
{
	int msgid = getMsgQueue();
	char buf_send[MYSIZE];
	char buf_recv[2*MYSIZE];
	// first server recerve msg, then send msg to client
	while(1)
	{
		printf("please Enter:");
		fflush(stdout);

		ssize_t _s = read(0,buf_send,sizeof(buf_send)-1);
		if(_s > 0){
		//	printf("-------------_s = %d\n", _s);
			buf_send[_s-1] = '\0';
			sendMessage(msgid, CLIENT_TYPE, buf_send);
		}

		if(recvMessage(msgid, SERVER_TYPE, buf_recv) != 0)
		{
			perror("recerve error");
			break;
		}
		printf("server echo# %s\n", buf_recv);
	}
	return 0;
}
