#include "jsonApi.h"

using namespace std;

int jsonApi::serialize(const Json::Value &val, std::string& outString)
{
#ifdef _FAST_
	Json::FastWriter w;
	outString = w.write(val);
#else
	Json::StyledWriter w;
	outString = w.write(val);
#endif
	return 0;
}

int jsonApi::deSerialize(Json::Value& val, std::string &inString)
{
	Json::Reader r;
	if(r.parse(inString, val, false))
	{
		return 1;
	}
	return 0;
}
