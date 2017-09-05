#include "Socket.h"

using namespace tdy
{

	// Socket class--------------------------------------------------
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


	//DataSocket class-----------------------------------------------
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

		//获取本地协议地址信息
		err = getsockname(m_sock, (struct sockaddr *)(&m_local_info), &addr_len);
		if (err != 0)
		{
			cout << "data socket getsockname error!" << endl;
			return -1;
		}
	}

	int DataSocket::Send(const char *p_buf, int p_size)
	{
		if (!m_connected)
		{
			cout << "data socket send not connected!" << endl;
			return = -1;
		}

		int send_len = send(m_sock, p_buf, p_size, 0);
		if (send_len == -1)
		{
			cout << "data socket send data error!" << endl;
			return -1;
		}

		return send_len;
	}

	int DataSocket::Receive(char *p_buf, int p_size)
	{
		if (!m_connected)
		{
			cout << "data socket receive not connected!" << endl;
			return -1;
		}

		int recv_len = recv(m_sock, p_buf, p_size, 0);
		if (recv_len == 0)
		{
			cout << "data socket receive connection closed!" << endl;
			return -1;
		}
		if (recv_len == -1)
		{
			cout << "data socket receive data error!" << endl;
			return -1;
		}

		return recv_len;
	}

	void DataSocket::Close()
	{
		Socket::Close();
		m_connected = false;
	}



	//ListenSocket---------------------------------------------------
	int ListenSocket::Listen(uint16_t p_port)
	{
		if (m_sock == -1)
		{
			m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (m_sock == -1)
			{
				cout << "listen socket create error!" << endl;
				return -1;
			}
		}

		//设置重用本地地址和端口
		bool b_reuse = true;
		int err = setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&b_reuse, sizeof(bool));
		if (err != 0) 
		{
			cout << "listen socket setsockopt error!" << endl;
			return -1;
		}

		//设置socket address
		m_local_info.sin_family = AF_INET;
		m_local_info.sin_port = htons(p_port);
		m_local_info.sin_addr.s_addr = htonl(INADDR_ANY);
		bzero(&(m_local_info.sin_zero), 8);

		//bind
		err = bind(m_sock, (struct sockaddr*)&m_local_info, sizeof(struct sockaddr));
		if (err == -1)
		{
			cout << "listen socket bind socketaddress error!" << endl;
			return -1;
		}

		err = listen(m_sock, 8);
		if (err == -1)
		{
			cout << "listen socket listen error!" << endl;
			return -1;
		}
		m_listening = true;
	}

	DataSocket ListenSocket::Accept()
	{
		sock_t data_sock;
		struct sockaddr_in data_addr;

		//接收套接字
		socket_t sock_len = sizeof(struct sockaddr);
		data_sock = accept(m_sock, (struct sockaddr *)&data_addr, &sock_len);
		if (data_sock == -1)
		{
			cout << "listen socket accept error!" << endl;
			return DataSocket();
		}
		return DataSocket(data_sock);
	}

	void ListenSocket::Close()
	{
		Socket::Close();
		m_listening = false;
	}
}
