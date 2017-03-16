#include "comm.h"
#include <unistd.h>

int main()
{
	int semid = creatSemSet(1);//yuan su de ge shu
    int ret = initSem(semid, 0);
	pid_t id = fork();
	if(id < 0)
	{

	}
    if(ret < 0)
    {
    	perror("semop");
    	return -1;
    }
	P(semid, 0);
	sleep(5);
	V(semid, 0);
	destorySemSet(semid);
	return 0;
}
