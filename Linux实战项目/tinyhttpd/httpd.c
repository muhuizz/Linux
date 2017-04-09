#include "httpd.h"

void print_log(const char * msg, int type)
{
	openlog();
//	time_t t;
//	struct tm* timeinfo;
//	time(&t);
//	timeinfo = localtime(&t);
//	printf("%s\n", asctime(timeinfo));
//	printf("%s\n", msg);
}

void echo_errno()
{

}

static int GetLine(int sock, char *buf, int sz)
{
	int i = 0;
	char c = '\0';
	while(i < sz-1 && c != '\n')
	{
		if( recv(sock, &c , 1, 0) > 0)
		{
			if(c == '\r')
			{
     			if( recv(sock, &c, 1, MSG_PEEK) > 0 && c == '\n')
     				recv(sock, &c, 1, 0);
     			else
     				c = '\n';
			}
			buf[i++] = c;
		}
		else
			c = '\n';
	}
	buf[i] = '\0';
	return i;
}

void clear_header(int sock)
{
	char buf[SIZE];
	int ret = -1;
	do
	{
		ret = GetLine(sock, buf, sizeof(buf));
	}while(ret != 1 && strcmp(buf, "\n") != 0);
}
int echo_www(int sock,const char*  path, int _s)
{
	int ret = 0;
	int fd = open(path, O_RDONLY);
	if(fd < 0)
	{
		ret = 8;
		print_log("open file faild", FATAL);
		echo_errno();
	}
	char buf[1024];
	strcpy(buf, "HTTP/1.0 200 ok\r\n");
	send(sock, buf, strlen(buf), 0);
	strcpy(buf, "\r\n");
	send(sock, buf, strlen(buf), 0);

	if(sendfile(sock, fd, 0, _s) < 0)
	{
		echo_errno();
		ret = 9;
	}
	close(fd);
	return ret;
}


int exec_cgi(int sock, const char* path, const char* method, const char* query_string)
{
	int ret = 0;
	int content_len = -1;
	char buf[SIZE];
	if(strcasecmp(method, "GET") == 0)
	{
		clear_header(sock);
	}
	else	// POST
	{
		do	
		{
			int ret = GetLine(sock, buf, sizeof(buf));
			if(ret > 0 && (strncmp(buf, "Content-Length", 14) == 0))
			{
				content_len = atoi(buf + 16);
			}
		}while(ret != 1 && strcmp(buf, "\n") != 0);

		if(content_len <= 0)
		{
			echo_errno();
			ret = 10;
		}
	}

	  
	int input[2];
	int output[2];
	pipe(input);
	pipe(output);

	pid_t id = fork();
	if(id < 0)
	{
		echo_errno();
		perror("fork");
		ret = 11;
	}
	else if(id == 0)	// child
	{
		close(input[1]);
		close(output[0]);
		dup2(input[0],0);
		dup2(output[1],1);

		char method_env[SIZE/8];
		char query_string_env[SIZE/4];
		char content_length_env[SIZE/8];
		sprintf(method_env, "METHOD=%s", method);
		putenv(method_env);
		if( strcasecmp(method, "GET") == 0 )
		{
			sprintf(query_string_env, "QUERY_STRING=%s", query_string);
			putenv(query_string_env);
		}
		else
		{
			sprintf(content_length_env, "CONTENT_LENGTH=%d", content_len);
			putenv(method_env);
		}
		execl(path, path, NULL);
		exit(1);
	}
	else	// father
	{
		close(input[0]);
		close(output[1]);
	//	dup2();
	//	dup2();
		if(strcasecmp(method, "POST") == 0)
		{
			int ch = 0;
			int i = 0;
			for(; i < content_len; i++)
			{
				recv(sock, &ch, 1, 0);
				write(input[1], &ch, 1);
			}
		}

		sprintf(buf,"HTTP/1.0 200 OK\r\n" );
		send(sock, buf, strlen(buf), 0);
		sprintf(buf, "Content-type:text/html;charset=utf-8\r\n");
		send(sock, buf, strlen(buf), 0);
		send(sock, "\r\n", strlen("\r\n"), 0);

		char ch = 0;
		while(read(output[0], &ch, 1) > 0)
		{
			send(sock, &ch, 1, 0);
		}
		waitpid(id, NULL, 0);
	}
	return ret;
}


int handle_client(int sock)
{
	char buf[SIZE];
	char method[64];
	char url[SIZE];
	char path[SIZE];
	int ret = 0;
	int cgi = 0;
	int i = 0;	// method/url
	int j = 0;	// buf
	char *query_string = NULL;
	memset(buf, 0, sizeof(buf));
	GetLine(sock, buf, sizeof(buf));

	printf("Recv msg is %s",  buf);
	
	// GET /AA/BB/CC?a=x&b=y HTTP/1.0
	// get method
	memset(method, 0, sizeof(method));
	while(i < sizeof(method)&& j < sizeof(buf) && !isspace(buf[j]))
	{
		method[i] = buf[j];
		i++;
		j++;
	}
	// match method
	if((strcasecmp(method, "GET")!= 0) && (strcasecmp(method, "POST")!= 0))
	{
		print_log("don't match method",FATAL );
		echo_errno();
		ret = 6;
		goto end;
	}
	//POST-->cgi
	if(strcasecmp(method, "POST") == 0)
		cgi=1;
	
	// jump blank
	while(j < sizeof(buf)-1 && isspace(buf[j]))
		j++;
	
	//url
	i =  0;
	memset(url, 0, sizeof(url));
	while(i < sizeof(url) && j < sizeof(buf) && !isspace(buf[j]))
	{
		url[i] = buf[j];
		i++;
		j++;
	}
	// cgi judge
	if(strcasecmp(method, "GET") == 0)
	{
		i = 0;
		query_string = url;
		while(i < sizeof(url) && *query_string != '?')
		{
			i++;
			query_string++;
		}
		if(*query_string == '?')
		{
			*query_string = '\0';
			query_string++;
			cgi=1;
		}
	}
	// printf("buf# [%s]\n method# [%s]\n query# [%s]\n", buf, method, query_string);

	// GET or POST
	// cgi -> ok
	// cgi -> GET(query_string) POST(recv...)
	
	// url ---> path
	sprintf(path, "wwwRoot%s", url);

	if(path[strlen(path)-1] == '/')
		strcat(path, "index.html");
	// judge file
	struct stat st;
	if(stat(path, &st) < 0)
	{
		// echo_errno(404)
		ret = 7;
		print_log("path is not exist", FATAL);
		goto end;
	}
	else
	{
		if(S_ISDIR(st.st_mode))
		{
			strcat(path, "/index.html");
		}
		else if(st.st_mode & (S_IXUSR|S_IXGRP|S_IXOTH ))
		{
			cgi =1;
		}
	}
	printf("Debug# path is %s\n", path);

	// cgi or normal
	if(cgi == 1)
	{
		ret = exec_cgi(sock, path, method, query_string);
	}
	else
	{
		clear_header(sock);
		ret = echo_www(sock, path, st.st_size);
	}

end:
	close(sock);
	return ret;
}

