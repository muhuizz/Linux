#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
int main()
{
	pid_t id =fork();
	if(id == 0)	// child
	{
		printf("hello child: pid->%d, ppid->%d \n",\
				getpid(), getppid());
		char* const myexec[] = {"ls", "-a", "-l", NULL};
		//execl("/bin/ls","ls","-a","-l",NULL);
		//execlp("ls", "ls", "-a", "-l", NULL);
		//execv("/bin/ls",myexec);
		//execvp("ls",myexec);

		char* const myenv[] = {"myPATH=/AA/BB/CC", NULL};
		execle("/home/muhui/code/bit_3/exec/test", "./test", NULL, myenv);

		printf("execl error\n");
		exit(1);
	}
	else	//father
	{
		sleep(1);		
		printf("hello father: pid->%d, ppid->%d \n",\
				getpid(), getppid());
		wait(NULL);
	}
	return 0;
}
