#include "comm.h"

int main()
{
	int msgid = createMsgQueue();
	char buf[2*MYSIZE];
	// first server recerve msg, then send msg to client
	while(1)
	{
		if(recvMessage(msgid, CLIENT_TYPE, buf) != 0)
		{
			perror("recerve error");
			break;
		}
		printf("client# %s \n", buf);
		if(sendMessage(msgid, SERVER_TYPE, buf) != 0)
		{
			perror("send error");
			break; 
		}
	}
	destoryMsgQueue(msgid);
	return 0;
}
