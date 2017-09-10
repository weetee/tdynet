#ifndef TDY_NET_TYPES_H
#define TDY_NET_TYPES_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

typedef int sock_t;	//套接字类型

#define MAX_BACKLOG_COUNT 5 	//accept阻塞队列的最大长度，也就是等待accept的socket的最大数量

#define MAX_BUFF_SIZE 1024

#endif //TDY_NET_TYPES_H