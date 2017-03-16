#ifndef __COMM_H
#define __COMM_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

#define PATHNAME "." 
#define PROJID 0x6666
#define MYSIZE 128

#define SERVER_TYPE 1
#define CLIENT_TYPE 2

struct msgbuf{
	long mtype;
	char mtext[MYSIZE];
};


int createMsgQueue();
int getMsgQueue();
int sendMessage(int msg_id, long type, const char* msg);
int recvMessage(int msg_id, int type, char out[]);
int destoryMsgQueue(int msg_id);

#endif
