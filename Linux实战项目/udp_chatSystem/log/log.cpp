#include "log.h"

using namespace std;

const static std::string stat[]={
	"NORMAL",
	"NOTICE",
	"WARNING",
	"FATAL",
};



void print_log(const char* msg, int level)
{
	cout<<msg<<"---"<<stat[level]<<endl;
}
