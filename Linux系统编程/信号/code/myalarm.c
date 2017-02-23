#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int count = 0;
void my_sig(int i)
{
//	alarm(1);
	printf("count = %d\n", count);
}
int main()
{
	signal(SIGALRM, my_sig);
	alarm(1);
	while(1)
	{
		count++;
	//	printf("count = %d\n", count);
	}
	return 0;
}
