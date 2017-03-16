#ifndef _COMM_
#define _COMM_

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define PATHNAME "."
#define PROJID	0x6666


union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *_buf;
};

int creatSemSet(int nums);
int initSem(int semid, int which);
int getSemSet();
int P(int semid,int witch);
int V(int semid,int witch);
int destorySemSet(int semid);



#endif
