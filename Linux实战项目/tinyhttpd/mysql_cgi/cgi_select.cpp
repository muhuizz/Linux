#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1024
#include "mysql_api.h"

void cgi_select(char *content_data)
{
	sql_cgi obj;
	obj.sql_connect_cgi();
	printf("<html><h1>");
	obj.sql_select_cgi();
	printf("</h1></html>");
}

int main()
{
	char method[SIZE/8];
	char content_len[SIZE/8];
	char content_data[SIZE/4];
	int len = -1;
	if(getenv("METHOD"))
	{
		strcpy(method,getenv("METHOD"));
	}
	else
	{
		perror("NOT METHOD");
		return 1;
	}
	if(strcasecmp(method, "GET") == 0)
	{
		if(getenv("QUERY_STRING"))
		{
			strcpy(content_data, getenv("QUERY_STRING"));
		}
		else
		{
			perror("NOT QUERY_STRING");
			return 2;
		}
	}
	else // POST
	{
		if(getenv("CONTENT_LENGTH"))
		{
			strcpy(content_len, getenv("CONTENT_LENGTH"));
			len=atoi(content_len);
			int i =0;
			int ch = '\0';
			for (;i < len; i++)
			{
				if(read(0, &ch, 1))
				{
					content_data[i] = ch; 
				}
			}
			content_data[i]='\0';
		}
		else
		{
			perror("NOT CONTENT_LENGTH");
			return 3;
		}
	}
	
	cgi_select(content_data); 
	return 0;
}

