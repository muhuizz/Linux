#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	umask(0);
	if(mkfifo("./myfifo", S_IFIFO | 0666) != 0)	// create failed
	{
		perror("mkfifo");
		return 1;
	}

	int fd=open("./myfifo",O_RDONLY);
	if(fd < 0)
	{
		perror("open for read error");
		exit(1);
	}
	char buf[2014];
	while(1)
	{
		memset(buf, 0, sizeof(buf));
		printf("please waiting...\n");
		ssize_t _s = read(fd,buf, sizeof(buf)-1);
		printf("client# %s\n", buf);
		if(_s > 0)
		{
			buf[_s] = '\0';
			printf("client# %s\n", buf);
		}
		//printf("Debug# %s\n", buf);
	}
	close(fd);	// close fifo
	return 0;
}
