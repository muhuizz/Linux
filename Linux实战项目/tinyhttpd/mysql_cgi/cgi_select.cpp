#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1024

void cgi_math(char *content_data)
{
	char *dat[3];
	int i = 0;
	char *cur = content_data;
	while(*cur)
	{
		if(*cur == '=')
		{
			dat[i] = cur+1;
			i++;
		}
		else if(*cur == '&')
		{
			*cur = '\0';
		}
		cur++;
	}

	int num1 =atoi(dat[0]);
	int num2 =atoi(dat[1]);
	printf("<html>\n");
	printf("<h1>%d + %d = %d</h1><br/>\n",num1, num2, num1+num2 );
	printf("<h1>%d - %d = %d</h1><br/>\n",num1, num2, num1-num2 );
	printf("<h1>%d * %d = %d</h1><br/>\n",num1, num2, num1*num2 );
	printf("<h1>%d / %d = %d</h1><br/>\n",num1, num2, num1/num2 );
	printf("</html>");
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
	// data is ready
	cgi_math(content_data); 
	return 0;
}

