#include "Types.h"

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
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(errno));
		exit(1);
	}

	lis_sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (lis_sock < 0)
	{
		fprintf(stderr, "create socket error: %s\n", gai_strerror(errno));
		exit(1);
	}

	freeaddrinfo(res);
	exit(0);
}

