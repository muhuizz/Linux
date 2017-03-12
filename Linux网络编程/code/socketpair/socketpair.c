#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int fd[2];
	socketpair(PF_LOCAL, SOCK_STREAM, 0,fd);
	pid_t id = fork();
	if(id < 0)
	{
		perror("fork");
		return 1;
	}
	else if(id == 0)	// child
	{
		close(fd[0]);
		while(1)
		{
			const char *msg = "hello bit";
			char *buf[1024];
			memset(buf, 0, sizeof(buf));
			write(fd[1], msg, strlen(msg));
			ssize_t _s = read(fd[1], buf, sizeof(buf));
			if(_s < 0)
			{
				perror("read");
				exit(2);
			}
			else
			{
				buf[_s] = 0;
				printf("echo# %s\n", buf);
			}
			sleep(1);
		}
		close(fd[1]);
	}
	else	// fatehr
	{
		close(fd[1]);
		while(1)
		{
			char buf[1024];
			memset(buf, 0, sizeof(buf));
			ssize_t _s = read(fd[0], buf, sizeof(buf));
			if(_s < 0)
			{
				perror("read");
				exit(2);
			}
			else
			{
				buf[_s] = 0;
				printf("Recv# %s\n", buf);
				buf[0] = 'H';
				write(fd[0], buf, sizeof(buf));
			}
		}
		close(fd[0]);
	}
	return 0;
}
















