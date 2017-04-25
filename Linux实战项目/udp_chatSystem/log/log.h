#ifndef __LOG_H__
#define __LOG_H__

#include <iostream>
#include <string>
#define NORMAL  0
#define NOTICE  1
#define WARNING 2
#define FATAL   3

void print_log(const char* msg, int level);

#endif// __LOG_H__
