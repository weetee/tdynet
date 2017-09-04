#ifndef TDY_NET_SOCKET_H
#define TDY_NET_SOCKET_H

#include "Types.h"

namespace tdy
{

class Socket
{
public:
	//获取套接字
	pid_t GetSock() const
	{
		return m_sock;
	}

	//获取Port
	uint16_t GetPort() const
	{
		return ntohs(m_local_info.sin_port);
	}

	//获取地址
	uint64_t GetAddress() const
	{
		return m_local_info.sin_addr.s_addr;
	}

	//关闭套接字
	void Close();

	//设置套接字是否阻塞
	void SetBlocking(bool p_block_mode);

protected:
	//构造函数
	Socket(pid_t p_sock = -1);

	//数据
	pid_t m_sock;
	struct sockaddr_in m_local_info;
	bool m_is_blocking;
};

//数据套接字类
class DataSocket : public Socket
{
public:
	DataSocket(pid_t p_sock = -1);

	//获取对端地址
	uint64_t GetRemoteAddress() const
	{
		return m_remote_info.sin_addr.s_addr;
	}

	//获取对端Port
	uint16_t GetRemotePort() const
	{
		return ntohs(m_remote_info.sin_port);
	}

	//查看是否有连接
	bool IsConnected() const
	{
		return m_connected;
	}

	//连接
	void Connect(uint64_t p_addr, uint16_t p_port);

	//发送数据
	int Send(const char *p_buf, int p_size);

	//接受数据
	int Receive(char *p_buf, int p_size);

	//关闭套接字
	void Close();

private:
	bool m_connected;
	struct sockaddr_in m_remote_info;
};


}	//namespace tdy end

#endif //TDY_NET_SOCKET_H