#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>

int main(void)
{
	int link_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (link_sock < 0)
	{
		print("create socket error\n");
		return -1;
	}

	struct sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(8888);
	sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bzero(&(sock_addr.sin_zero), 8);
}
