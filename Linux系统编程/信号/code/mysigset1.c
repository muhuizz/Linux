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

void runSig(int i)
{
	printf("run SIGINT\n");
}

int main()
{
	signal(SIGINT, runSig);
	sigset_t block, oblock, pending;
	sigemptyset(&block);
	sigaddset(&block, SIGINT);

	sigprocmask(SIG_SETMASK, &block, &oblock);
	int count = 0;
	while(1)
	{
		if(count == 10)
		{
			sigdelset(&block, SIGINT);
			sigprocmask(SIG_SETMASK, &block, &oblock);
		}
		sleep(1);
		sigpending(&pending);
		printfPending(&pending);
		count++;
	}
	printf("hello world\n");
	return 0;
}
