#include "comm.h"

int main()
{
	//int  getShm();
	int shmid = creatShm(5);
	sleep(5);
	char *mem = (char *)shmat(shmid, NULL, 0);
	sleep(5);
	shmdt(mem);
	sleep(5);
	destoryShm(shmid);
	return 0;
}
