#ifndef _HTTPD_H_
#define _HTTPD_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

#define NORMAL 0
#define WARNING 1
#define FATAL 2

#define SIZE 4096

int handle_client(int sock);
void print_log(const char * msg, int type);
int startup(const char *_ip, int _port);

#endif// _HTTPD_H_
