#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

//int g=6;
//const char buf[]="it's a nice day\n";
//
//int main()
//{
//	int value = 88;
//	pid_t pid;
//	if(write(2, buf, sizeof(buf)-1) != sizeof(buf)-1)
//	{
//		printf("write error\n");
//	}
//	
//	printf("before fork\n");
//	if((pid = fork()) < 0)	// fail
//	{
//		printf("fork error\n");
//	}
//	else if(pid == 0)	// child
//	{
//		g++;
//		value++;
//	}
//	else	// father
//	{
//		sleep(2);
//	}
//	printf("pid = %d , g = %d , value = %d\n",\
//			getpid(),g,value);
//			
//	return 0;
//}
int main()
{
	pid_t id;
	id = fork();
	if(id == 0)//child
	{
		printf("this is child process\n");
		sleep(3);
		//exit(0);
	}
	else//parent
	{
		printf("this is father rprocess\n");
		sleep(5);
		wait(NULL);
	}

	return 0;
}
