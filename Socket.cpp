#include "Socket.h"

void Socket::SetBlocking(bool p_block_mode)
{
	int flags = fcntl(m_sock, F_GETFL, 0);
	if (!p_block_mode)
	{
		flags |= O_NONBLOCK;
	}
	else
	{
		flags &= O_NONBLOCK;
	}

	int err = fcntl(m_sock, F_SETFL, flags);
	if (err == -1)
	{
		cout << "SetBlocking failed~!" << endl;
		return -1;
	}
	m_is_blocking = p_block_mode;
}