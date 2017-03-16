#ifndef _COMM_
#define _COMM_

#define PATHNAME "."
#define PROJID 0x6666
#define SIZE 4096

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int creatShm(int size);
int  getShm();
//int atShm();
//int dtShm();
int destoryShm(int shmid);

#endif
