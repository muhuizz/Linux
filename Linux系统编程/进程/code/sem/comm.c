#include "comm.h"

static int commSemSet(int nums,int flags)
{
	key_t _k = ftok(PATHNAME, PROJID);
	int semid = semget(_k, nums, flags);
	if(semid < 0)
	{
		perror("semid");
		return -1;
	}
	return semid;
}

int creatSemSet(int nums)
{
	int flags = IPC_CREAT|IPC_EXCL|0666;
	return commSemSet(nums, flags);
}

int initSem(int semid, int which)
{
	union semun un;
	un.val = 1;
	int ret = semctl(semid, which, SETVAL, un);
	if(ret < 0)
	{
		perror("initSem");
		return -1;
	}
	return 0;
}

int getSemSet()
{
//	return creatSemSet(num, IPC_CREAT);
	return commSemSet(0, 0);
}

static int Semop(int semid, int which, int op)
{
	struct sembuf s;
	s.sem_num = which;
	s.sem_op = op;
	s.sem_flg = 0;

	int ret = semop(semid, &s, 1);
	if(ret< 0)
	{
		return -1;
	}
	return 0;
}

int P(int semid,int which)
{
	return Semop( semid, which, -1);
}
int V(int semid,int which)
{
	return Semop( semid, which, 1);
}
int destorySemSet(int semid)
{
	int ret = semctl(semid, 0, IPC_RMID);
	if(ret < 0)
	{
		perror("semctl");
		return -1;
	}
	return 0;
}
















