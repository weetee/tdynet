#ifndef TDY_NET_TYPES_H
#define TDY_NET_TYPES_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

namespace tdy
{
	typedef int sock_t;
}	//namespace tdy end


#endif //TDY_NET_TYPES_H