#include<sys/stat.h>  
#include<unistd.h>  
#include<fcntl.h>  
#include<stdio.h>  
#include<stdlib.h>  
#include<errno.h>  
#include<string.h>  
#include<signal.h>  
#define ERR_EXIT(m) \
do{perror(m);   exit(EXIT_FAILURE);  } while(0)  
  
int main(int argc, char *argv[])  
{  
    int pipefd[2];  
    if (pipe(pipefd) == -1)  
        ERR_EXIT("pipe error");  
    int ret;  
    int count = 0;  
    int flags = fcntl(pipefd[1], F_GETFL);  
    fcntl(pipefd[1], F_SETFL, flags | O_NONBLOCK); // 设置为非阻塞  
    while (1)  
    {  
        ret = write(pipefd[1], "A", 1);  
        if (ret == -1)  
		{  
            printf("err=%s\n", strerror(errno));  
            break;  
		}  
		count++;  
	}  
	printf("count=%d\n", count); //管道容量  
	return 0;  
}
