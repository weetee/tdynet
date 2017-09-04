#ifndef TDY_NET_SOCKET_H
#define TDY_NET_SOCKET_H

#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>

class Socket
{
	void SetBlocking(bool p_block_mode);
};

#endif //TDY_NET_SOCKET_H