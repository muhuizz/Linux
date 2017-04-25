#ifndef __DATATYPE_H__
#define __DATATYPE_H__

#include <iostream>
#include <string>
#include "jsonApi.h"
class datatype
{
public:
	int valueToString(std::string& outString);
	
	int stringToValue(std::string& inString);
public:
	std::string nick_name;
	std::string school;
	std::string msg;
	std::string cmd;
};


#endif// __DATATYPE_H__
