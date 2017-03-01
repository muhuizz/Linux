#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
int g=6;

void fun()
{
	printf("child exit\n");
}
int main()
{
	int value = 88;
	pid_t pid;
	
	printf("before fork\n");
	if((pid = vfork()) < 0)	// fail
	{
		printf("fork error\n");
	}
	else if(pid == 0)	// child
	{
		atexit(fun);
		g++;
		value++;
		printf("child: \n");
		sleep(2);
		exit(0);
	}
	else	// father
	{
		printf("father: \n");
		printf("pid = %d , g = %d , value = %d\n",\
			getpid(),g,value);
	}
	return 0;
}

