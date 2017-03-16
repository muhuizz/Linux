#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main()
{
	//1.create pipe
	int fd[2] = {0};
	if(pipe(fd) != 0)
	{
		perror("pipe error");
		return 1;
	}
	printf("fd[0] = %d, fd[1] = %d\n",fd[0], fd[1]);

	// 2.create child progress

	pid_t id = fork();
	// 3.close suitable port
	if(id == 0)	// child write
	{ 
		close(fd[0]);
		const char* msg = "child : IPC by pipe with father";
		int count = 5;
		while(1){
			write(fd[1], msg, strlen(msg));
			if(count--)
			{
				sleep(1);
			}
			else
			{
				break;
			}
			printf("child  is writing\n");
			
		}
		close(fd[1]);
		sleep(1);
		exit(0);
	}
	else
	{
		close(fd[1]);
		int count = 5;
		char* buf[1024];
		while(count--)
		{
			ssize_t _s = read(fd[0], buf, sizeof(buf)-1);
	 		if(_s > 0){
				buf[_s] = '\0';
				printf("father receive:%s\n", buf);
			}

		}
	//	while(1){
	//		ssize_t _s = read(fd[0], buf, sizeof(buf)-1);
	//		if(_s > 0){
	//			buf[_s] = '\0';
	//			printf("father receive:%s\n", buf);
	//		}
	//		else if (_s == 0)	// end of pipe
	//		{
	//			printf("read end of file!\n");
	//			break;
	//		}
	//		else
	//		{
	//			perror("read");
	//			exit(1);
	//		}
	//	}
		int status = 0;
		pid_t ret = waitpid(id, &status, 0);
		if(ret == id)
		{
			printf("wait child success\n");
		}
		else
		{
			printf("wait child filed\n");
		}
	}
	return 0;
}
