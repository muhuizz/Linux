#ifndef __JSONAPI_HPP__
#define __JSONAPI_HPP__

#include <iostream>
#include <json/json.h>
#include <string>

class jsonApi
{
public:
	// xu lie hua 
	static int serialize(const Json::Value &val, std::string& outString);

	// fan xu lie hua
	static int deSerialize(Json::Value& val, std::string &inString);
};

#endif// __JSONAPI_H__
