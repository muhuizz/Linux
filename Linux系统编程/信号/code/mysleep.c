#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void run_alarm(int i)
{}
/*
size_t mysleep(size_t second)
{
	signal(SIGALRM, run_alarm);
	alarm(second);
	pause();
	int ret = alarm(0);
	return ret;
}
*/
size_t mysleep(size_t second)
{
	struct sigaction act, oact;
	act.sa_handler = run_alarm;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	sigaction(SIGALRM, &act, &oact);
	alarm(second);
	pause();
	int ret = alarm(0);

	sigaction(SIGALRM, &oact, NULL);
	return ret;
}
int main()
{
	while(1)
	{
		mysleep(2);
		printf("this is mysleep\n");
	}
	return 0;
}
