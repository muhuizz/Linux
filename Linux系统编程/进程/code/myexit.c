#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	printf("hello world");
	sleep(3);
	exit(0);
	///_exit(0);
	return 0;
}
