#include "mysql_api.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1024

void cgi_modify(char *content_data)
{
	char *dat[10];
	int index = 0;
	char *cur = content_data;
	const char *column[3] = {"age", "school", "id"};
	while(*cur)
	{
		if(*cur == '=')
		{
			dat[index++] = cur+1;
		}
		else if(*cur == '&')
		{
			*cur = '\0';
		}
		cur++;
	}
	string condition;
	string info;
	condition += "name = ";
	condition += "'";
	condition += dat[0];
	condition += "'";

	for(int i = 0; i < index-1; i++)
	{
		info+=column[i];
		info += " = '";
		info+=dat[i+1];
		info += "' ";
		if(i!= index-2)
			info+=",";
	}
	sql_cgi myapi;
	myapi.sql_connect_cgi();
	if (myapi.sql_update_cgi(condition, info) == 0)
	{
		cout<<"<html><br><h1>"<<"Update success!"<<"</h1><br></html>"<<endl;
	}
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
			return 3;
		}
	}
	// data is ready
	cgi_modify(content_data); 
	return 0;
}

