#include "Socket.h"

using namespace tdy
{

	// Socket class
	Socket::Socket(sock_t p_sock) : m_sock(p_sock)
	{
		if (p_sock != -1)
		{
			socklen_t addr_len = sizeof(m_local_info);
			getsockname(p_sock, (sockaddr *)(&m_local_info), &addr_len);
		}
		
		//默认设置为阻塞
		m_is_blocking = true;
	}

	void Socket::Close()
	{
		close(m_sock);
		m_sock = -1;	//invalidate m_sock
	}

	int Socket::SetBlocking(bool p_block_mode)
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
		return 0;
	}


	//DataSocket class
	DataSocket::DataSocket(sock_t p_sock)
		: Socket(p_sock), m_connected(false)
	{

	}
}
