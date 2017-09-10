#include "Types.h"

void LoggingError(const char *p_errstr)
{
	fprintf(stderr, "Tcp Client %s error: %s\n", p_errstr, gai_strerror(errno));
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "usage: must input ipaddress and port\n");
		exit(1);
	}

	int err;
	sock_t cli_sock;

	struct addrinfo hints, *res;
	bzero(&hints, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	//获取地址结构
	err = getaddrinfo(argv[1], argv[2], &hints, &res);
	if (err != 0)
	{
		LoggingError("getaddinfo");
		exit(1);
	}

	//创建套接字
	cli_sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (cli_sock < 0)
	{
		LoggingError("create socket");
		exit(1);
	}

	//连接
	err = connect(cli_sock, res->ai_addr, res->ai_addrlen);
	if (err != 0)
	{
		LoggingError("connect socket");
		exit(1);
	}

	//数据传输
	char *msg = "Hello server!";
	int send_len;	//发送数据的长度
	send_len = send(cli_sock, msg, sizeof(msg), 0);
	if (send_len == -1)
	{
		LoggingError("send data to server");
		exit(1);
	}


	//释放
	freeaddrinfo(res);
	exit(0);
}
