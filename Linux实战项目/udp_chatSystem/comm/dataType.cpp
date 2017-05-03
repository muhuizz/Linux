#include "dataType.h"

using namespace std;

int datatype::valueToString(string& outString)
{
	Json::Value v;
	v["nick_name"] = nick_name;
	v["school"] = school;
	v["msg"] = msg;
	v["cmd"] = cmd;
	return jsonApi::serialize(v, outString);
}

int datatype::stringToValue(string& inString)
{
	Json::Value v;
	jsonApi::deSerialize(v,inString);
	nick_name = v["nick_name"].asString();
	school = v["school"].asString();
	msg = v["msg"].asString();
	cmd = v["cmd"].asString();
}

#ifdef _DEBUG_
int main()
{
	datatype dat;
	dat.nick_name = "zhangsan";
	dat.school = "SUST";
	dat.msg = "Hello world!";
	dat.cmd = "None";
	string str;
	dat.valueToString(str);
	cout<<str<<endl;
	cout<<endl;
	dat.stringToValue(str);
	return 0;
}
#endif
