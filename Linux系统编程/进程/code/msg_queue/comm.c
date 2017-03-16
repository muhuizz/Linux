#include "comm.h"

int commMsgQueue(int flag)
{
	key_t _k=ftok(PATHNAME, PROJID);
	if(_k < 0)
	{
		perror("fork error");
		return -1;
	}
	
	int msg_id = msgget(_k, flag);
	if(msg_id < 0)
	{
		perror("msgget error");
		return -2;
	}
	return msg_id;
}

int createMsgQueue()
{
	return commMsgQueue(IPC_CREAT | IPC_EXCL| 0666 );
}

int getMsgQueue()
{
	return commMsgQueue(IPC_CREAT);
}
int sendMessage(int msg_id, long type, const char* msg)
{
	struct msgbuf buf;
	buf.mtype = type;	// the sender
	strcpy(buf.mtext,msg);
	int ret = msgsnd(msg_id, &buf, sizeof(buf.mtext), 0);
	if(ret != 0)
	{
		perror("send error");
		return -1;
	}
	else
		return 0;
}
int recvMessage(int msg_id, int type, char out[])
{
	struct msgbuf buf;
	int size = msgrcv(msg_id,&buf, sizeof(buf.mtext),type, 0 );
	if(size > 0)
	{
		buf.mtext[size-1] = '\0';
		strncpy(out, buf.mtext, size);
		return 0;
	}

	perror("recerve error");
	return -1;
}
int destoryMsgQueue(int msg_id)
{
	if(msgctl(msg_id, IPC_RMID, NULL)< 0)
	{	
		perror("msgctl error");
		return -1;
	}
	return 0;
}
