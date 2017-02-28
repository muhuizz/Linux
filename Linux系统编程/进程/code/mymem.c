#include <stdio.h>
#include <stdlib.h>

int g_val = 10;
int g_val1;
int main(int argc, char* argv[],char* env[])
{
	int* mem1 = (int*)malloc(4);
	int* mem2 = (int*)malloc(4);
	int* mem3 = (int*)malloc(4);
	int* mem4 = (int*)malloc(4);
	const char* msg = "hello world";
	int a;
	int b;
	int c;
	printf("code : %p\n", main);
	printf("read only : %p\n",msg);
	printf("g init value: %p\n",&g_val);
	printf("uninit value: %p\n",&g_val1);
	printf("heap1: %p\n",mem1);
	printf("heap2: %p\n",mem2);
	printf("heap3: %p\n",mem3);
	printf("heap4: %p\n",mem4);
	printf("stack: %p\n", &msg);
	printf("stack: %p\n", &a);
	printf("stack: %p\n", &b);
	printf("stack: %p\n", &c);
	printf("argc与argv####################################\n");
	printf("argc addr : %p\n",&argc);
	int i = 0;
	for(; i< argc;i++)
	{
		printf("%d -> %s --> %p\n", i, argv[i] );
	}
	printf("环境变量####################################\n");
	for(i=0;env[i] != NULL;i++)
	{
		printf("%d -> %s --> %p\n", i, env[i]);
	}
	return 0;
}
