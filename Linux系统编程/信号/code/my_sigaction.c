#include <stdio.h>
#include <signal.h>


void IntRun(int i)
{
	printf("my sigaction is running\n");
}


int main()
{
	struct sigaction act, oact;
	act.sa_handler = IntRun;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGINT, &act, &oact);
	while(1)
	{
		sleep(1);
		printf("hello world\n");
	}
	return 0;
}
