#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>

#define MAX_LINK_COUNT 	16 		//最大连接数
#define MAX_BUFFSIXE	1024

int main(void)
{
	int err = 0;
	int listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listen_sock < 0)
	{
		printf("create socket error!\n");
		return -1;
	}

	printf("socket created!");

	struct sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(8888);
	sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bzero(&(sock_addr.sin_zero), 8);

	socklen_t sa_size = sizeof(struct sockaddr_in);
	if (bind(listen_sock, (struct sockaddr *)&sock_addr, sa_size) != 0)
	{
		printf("bind socket error!\n");
		return -1;
	}

	if (listen(listen_sock, MAX_LINK_COUNT) != 0)
	{
		printf("listen socket error!\n");
		return -1;
	}

	char recv_buff[MAX_BUFFSIXE];
	while (1)
	{
		struct sockaddr_in client_addr;
		socklen_t cli_len = sizeof(struct sockaddr_in);
		int conn_sock = accept(listen_sock, (struct sockaddr *)&client_addr, cli_len);
		if (conn_sock < 0 )
		{
			printf("accept socket error!\n");
		}
		if (recv(conn_sock, &recv_buff, MAX_BUFFSIXE, 0) < 0)
		{
			printf("recv data error!\n");
		}
		else
		{
			printf("received data %s\n", recv_buff);
		}
		close(conn_sock);
	}
	close(listen_sock);

	exit(0);
}
