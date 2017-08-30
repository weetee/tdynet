#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

int main(void)
{
	int link_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (link_socket < 0)
	{
		print("create socket error\n");
		return -1;
	}
}
