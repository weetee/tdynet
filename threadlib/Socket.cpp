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
		if (p_sock != -1)
		{
			socklen_t addr_len = sizeof(m_remote_info);
			getpeername(p_sock, (sockaddr *)(&m_remote_info), &addr_len);
			m_connected = true;
		}
	}

	int DataSocket::Connect(uint64_t p_addr, uint16_t p_port)
	{
		if (m_connected)
		{
			cout << "this data socket already in connected..." << endl;
			return -1;
		}

		if (m_sock == -1)
		{
			m_sock = socket(AF_INET, SOCK_STREAM, IPPROTE_TCP);
			if (m_sock == -1)
			{
				cout << "create data socket error!" << endl;
				return -1;
			}
		}

		m_remote_info.sin_family = AF_INET;
		m_remote_info.sin_port = htons(p_port);
		m_remote_info.sin_addr.s_addr = p_addr;
		bzero(&(m_remote_info.sin_zero), 8);

		socklen_t addr_len = sizeof(sockaddr);
		int err = connect(m_sock, (struct sockaddr *)(&m_remote_info), addr_len);
		if (err == -1)
		{
			cout << "connect data socket error!" << endl;
			return -1;
		}

		m_connected = true;
	}
}
