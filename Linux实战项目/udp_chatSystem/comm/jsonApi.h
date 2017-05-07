#ifndef __JSONAPI_HPP__
#define __JSONAPI_HPP__

#include <iostream>
#include <json/json.h>
#include <string>

class jsonApi
{
public:
	static int serialize(const Json::Value &val, std::string& outString);

	static int deSerialize(Json::Value& val, std::string &inString);
};

#endif// __JSONAPI_H__
