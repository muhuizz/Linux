#include "comm.h"


static int comShm(int n, int flag)
{
	key_t _k = ftok(PATHNAME, PROJID);
	if(_k < 0)
	{
		perror("ftok");
		return -1;
	}
	int shmid = shmget(_k, n*SIZE, flag);
	if(shmid < 0)
	{
		perror("shmget");
		return -2;
	}
	return shmid;
}
int creatShm(int size)
{
	int flag = IPC_CREAT | IPC_EXCL|0666; 
	return comShm(size, flag);
}
int  getShm()
{
//	return comShm(0, 0);
	return comShm(0, IPC_CREAT);
}
//int atShm();
//int dtShm();
int destoryShm(int shmid)
{
	if(shmctl(shmid, IPC_RMID, NULL) < 0)
	{
		perror("shmctl");
		return -1;
	}
	return 0;
}





