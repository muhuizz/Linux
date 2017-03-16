#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int fd=open("./myfifo",O_WRONLY);
	if(fd < 0)
	{
		perror("open for read error");
		exit(1);
	}
	char buf[2014];
	char *msg = "hello world";
	while(1)
	{
		memset(buf, 0, sizeof(buf));
		ssize_t _s = read(0, buf, sizeof(buf)-1);
		if(_s > 0)
		{
			buf[_s-1] = 0;
			write(fd, msg, strlen(buf));
		}
		sleep(1);
	//	printf("Debug# %s\n",msg);
	}
	close(fd);
	return 0;
}
