#include <stdio.h>
#include <signal.h>

void printfPending(sigset_t *pending)
{
	int i = 1;
	for(;i <= 31; i++)
	{
		if(sigismember(pending, i)){
			printf("1");
		}
		else{
			printf("0");
		}
	}
	printf("\n");
}
int main()
{
	sigset_t block, oblock, pending;
	sigemptyset(&block);
	sigaddset(&block, SIGINT);

	sigprocmask(SIG_SETMASK, &block, &oblock);
	while(1)
	{
		sleep(1);
		sigpending(&pending);
		printfPending(&pending);
	}
	printf("hello world\n");
	return 0;
}
