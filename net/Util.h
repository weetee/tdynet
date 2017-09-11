#ifndef TDY_NET_UTIL_H
#define TDY_NET_UTIL_H

#include "Types.h"

int SendAll(sock_t s, char *buf, int *len)
{
	int total = 0;
	int left = *len;
	int send_len;

	while (total < *len)
	{
		send_len = send(s, buf + total, left, 0);
		if (send_len == -1)
		{
			break;
		}
		total += send_len;
		left -= send_len;
	}

	*len = total;

	return n==-1?-1:0;
}

#endif //TDY_NET_UTIL_H