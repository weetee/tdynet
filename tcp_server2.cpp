// 使用select编写服务器代码

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdlib>
#include <errno.h>
#include <vector>
#include <iostream>

using namespace std;

#define MAX_LINK_COUNT 	16 		//最大连接数
#define MAX_BUFFSIXE	1024

int main(void)
{
	int err;
	int listen_sock;
	vector<int> sock_list;

	listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listen_sock == -1)
	{
		cout << "create socket error!" << endl;
		return -1;
	}

	struct sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(8888);
	sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bzero(&(sock_addr.sin_zero), 8);

	socklen_t sa_size = sizeof(struct sockaddr_in);
	err = bind(listen_sock, (struct sockaddr *)&sock_addr, sa_size);
	if (err < 0)
	{
		cout << "bind socket error!" << endl;
		return -1;
	}

	err = listen(listen_sock, MAX_LINK_COUNT);
	if (err < 0)
	{
		cout << "listen socket error!" << endl;
		return -1;
	}

	// 开始创建select函数所需
	fd_set read_set;
	struct timeval zero_time;	//值为0的timeval结构
	zero_time.tv_usec = 0;
	zero_time.tv_sec = 0;

	char recv_buff[MAX_BUFFSIXE];	//消息接收
	bool done = false;
	vector<int>::iterator itr;
	while (!done)
	{
		FD_ZERO(&read_set);
		FD_SET(listen_sock, &read_set);
		//将所有数据套接字加入read_set
		for (itr = sock_list.begin(); itr != sock_list.end(); itr++)
		{
			FD_SET(*itr, &read_set);
		}
		//调用select
		int i = select(0x7FFFFFFF, &read_set, NULL, NULL, &zero_time);
		if (i > 0) 	//i > 0 说明存在有活动的套接字
		{
			if (FD_ISSET(listen_sock, &read_set))	//检测监听套接字上是否有流入连接
			{
				int data_sock = accept(listen_sock, (struct sockaddr*)&sock_addr, &sa_size);
				sock_list.push_back(data_sock);
			}
		}
		for (itr = sock_list.begin(); itr != sock_list.end(); itr++)
		{
			if (FD_ISSET(*itr, &read_set))
			{
				err = recv(*itr, recv_buff, MAX_BUFFSIXE, 0);
				if (err == -1)
				{
					cout << "receive data error!" << endl;
					return -1;
				}
				else if (err == 0)	//关闭已经被断开连接的套接字
				{
					close(*itr);
					sock_list.erase(itr);
					--itr;
				}
				else
				{
					cout << "receive data: " << recv_buff << endl;
					if (strcmp(recv_buff, "quit") == 0)
					{
						done = true;
					}
				}
			}
		}
	}

	//关闭监听套接字
	close(listen_sock);

	for (int i = 0; i < sock_list.size(); i++)
	{
		close(sock_list[i]);
	}

	exit(0);
}
