#include "mysql_api.h"

sql_cgi::sql_cgi()
{
	conn=mysql_init(NULL);
}

sql_cgi::~sql_cgi()
{
	mysql_close(conn);
}

int sql_cgi::sql_connect_cgi()
{
	if(mysql_real_connect(conn,"127.0.0.1", "root", "123456", "sust" ,3306, NULL, 0 )== NULL)
		return -1;
	else
		return 0;
}
int sql_cgi::sql_select_cgi()
{
	string msg = "select * from student_info";
	MYSQL_RES *res;
	MYSQL_ROW row;
	MYSQL_FIELD *fd;
	if(mysql_real_query(conn, msg.c_str(),(unsigned long) msg.size()))
	{
		return -1;
	}
	res = mysql_store_result(conn);
	int line = mysql_num_rows(res);	
	int fields = mysql_num_fields(res);	
	fd = mysql_fetch_fields(res);
	for(int i =0; i < fields; i++)
	{
		cout<<fd[i].name<<"   ";
	}
	cout<<"<br>"<<endl;
	while(row = mysql_fetch_row(res))
	{
		for(int i = 0; i < fields-1; i++)
		{
			cout<<row[i]<<"   ";
		}
		cout<<"<br>"<<endl;
	}
	cout<<"<br><br>"<<endl;
	mysql_free_result(res);
	return 0;
}

#ifdef _DEBUG
int sql_cgi::sql_insert_cgi()
{
	string msg = "insert into student_info (name, sex, age, school) VALUES (";
	
	string info = "'muhui', 'man', 22, 'sust_dx'";
	msg+=info;
	msg+=')';
	if(mysql_real_query(conn, msg.c_str(),(unsigned long)msg.size()))
	{	
		return -1;
	}
	return 0;
}
int sql_cgi::sql_delete_cgi()
{
	string msg = "delete from student_info where id = 3";
	if(mysql_real_query(conn, msg.c_str(),(unsigned long) msg.size()))
	{
		return -1;
	}
	return 0;
}
int sql_cgi::sql_update_cgi()
{
	string msg = "update student_info SET name = 'lllzk' where id = 2";
	if(mysql_real_query(conn, msg.c_str(),(unsigned long) msg.size()))
	{
		return -1;
	}
	return 0;
}

int main()
{
	sql_cgi mycgi;
	if (mycgi.sql_connect_cgi() != 0)
	{
		cout<<"connect faild"<<endl;
		exit(1);
	}
	else
		cout<<"mysql is ready!"<<endl;
	if (mycgi.sql_insert_cgi() != 0)
	{
		cout<<"insert faild"<<endl;
	}
	else
		cout<<"insert successs"<<endl;
	if (mycgi.sql_delete_cgi() != 0)
	{
		cout<<"delete faild"<<endl;
	}
	else
		cout<<"delete successs"<<endl;
	if (mycgi.sql_select_cgi() != 0)
	{
		cout<<"select faild"<<endl;
	}
	else
		cout<<"select success"<<endl;
	return 0;
}

#else
int sql_cgi::sql_insert_cgi(const string& info)
{
	string msg = "insert into student_info (name, sex, age, school) VALUES (";
	
	msg+=info;
	msg+=')';
	if(mysql_real_query(conn, msg.c_str(),(unsigned long)msg.size()))
	{	
		return -1;
	}
	return 0;
}

int sql_cgi::sql_delete_cgi(const string& info)
{
	string msg = "delete from student_info where ";
	msg += info;
	if(mysql_real_query(conn, msg.c_str(),(unsigned long) msg.size()))
	{
		return -1;
	}
	return 0;
}

int sql_cgi::sql_update_cgi(const string& condition, const string& info)
{
	string msg = "update student_info SET "; 
	msg += info;
	msg += " where ";
	msg += condition;
	if(mysql_real_query(conn, msg.c_str(),(unsigned long) msg.size()))
	{
		return -1;
	}
	return 0;
}

#endif // _DEBUG
