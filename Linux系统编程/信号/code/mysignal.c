#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{


	int count = 0;
	while(1)
	{
		printf("hello world\n");
		if(count == 5)
		//	raise(9);
			abort();
		sleep(1);
		count++;
	}
/*
	if(argc != 3)
	{
		printf("Isn't form: ./file pid signo \n");
		return 1;
	}
	else
	{
		int pid = atoi(argv[1]);
		int sig = atoi(argv[2]);
		kill(pid, sig);
	}
*/
/*	while(1)
	{
		printf("hello bit\n");
		sleep(1);
	}
*/
	return 0;
}
