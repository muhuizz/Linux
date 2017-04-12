#include <iostream>
#include <mysql.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
using namespace std;


class sql_cgi
{
public:
	sql_cgi();
	~sql_cgi();
	int sql_connect_cgi();
	int sql_insert_cgi();
	int sql_delete_cgi();
	int sql_update_cgi();
	int sql_select_cgi();
	int sql_insert_cgi(string info);
protected:
	MYSQL* conn;
};



