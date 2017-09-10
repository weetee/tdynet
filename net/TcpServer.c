#include "Types.h"

void LoggingError(const char *p_errstr)
{
	fprintf(stderr, "Tcp Server %s error: %s\n", p_errstr, gai_strerror(errno));
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "usage: must need port !\n");
	}

	int err;
	sock_t lis_sock;	//监听socket

	struct addrinfo hints;	//need fill
	struct addrinfo *res;	//用于存放填充好的结构

	bzero(&hints, sizeof(hints));	//保证结构为空
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	err = getaddrinfo(NULL, argv[1], &hints, &res);
	if (err != 0)
	{
		LoggingError("begin getaddrinfo");
		exit(1);
	}

	//创建
	lis_sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (lis_sock < 0)
	{
		LoggingError("create socket");
		exit(1);
	}

	//bind
	err = bind(lis_sock, res->ai_addr, res->ai_addrlen);
	if (err != 0)
	{
		LoggingError("bind socket");
		exit(1);
	}

	//监听
	err = listen(lis_sock, MAX_BACKLOG_COUNT);
	if (err != 0)
	{
		LoggingError("listen socket");
		exit(1);
	}

	//数据
	char buf[MAX_BUFF_SIZE];
	struct sockaddr_storage cli_addr;	//通用地址结构创建存放连接的地址
	socklen_t addr_len = sizeof(cli_addr);

	sock_t data_sock = accept(lis_sock, (struct sockaddr *)&cli_addr, &addr_len);
	if (data_sock < 0)
	{
		LoggingError("accept client");
		exit(1);
	}

	int recv_len = recv(data_sock, buf, MAX_BUFF_SIZE, 0);
	if (recv_len == -1)
	{
		LoggingError("receive data");
		exit(1);
	}
	fprintf(stdout, "receive data: %s\n", buf);

	//获取远程信息
	struct sockaddr_in guest;
	int guest_len = sizeof(guest);
	char guest_ip[20];
	err = getpeername(data_sock, (struct sockaddr *)&guest, &guest_len);
	if (err < 0)
	{
		LoggingError("getpeername");
	}
	else
	{
		inet_ntop(AF_INET, &guest.sin_addr, guest_ip, sizeof(guest_ip));
		fprintf(stderr, "remote ip address: %s\n", guest_ip);
	}

	//关闭
	close(data_sock);
	close(lis_sock);
	//shutdown(data_sock, 0/1/2);

	freeaddrinfo(res);
	exit(0);
}

