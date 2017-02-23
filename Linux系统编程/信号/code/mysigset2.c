#include <stdio.h>
#include <signal.h>
int main()
{
	sigset_t block, oblock, pending;
	sigemptyset(&block);
	sigaddset(&block, SIGINT);

	sigprocmask(SIG_SETMASK, &block, &oblock);
	signal(SIGINT, SIG_IGN);
	while(1)
	{
		sleep(1);
	//	sigpending(&pending);
	//	printfPending(&pending);
		printf("hello bit\n");
	}
	printf("hello world\n");
	return 0;
}
