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
	int sql_select_cgi();
#ifdef _DEBUG	
	int sql_insert_cgi();
	int sql_delete_cgi();
	int sql_update_cgi();
#else
	int sql_insert_cgi(const string& info);
	int sql_delete_cgi(const string& info);
	int sql_update_cgi(const string& condition, const string& info);
#endif
protected:
	MYSQL* conn;
};



