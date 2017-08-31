#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <cstdlib>

using namespace std;
#define MAX_BUFFSIXE	1024

int main(void)
{
	int err = 0;
	string ip;
	cout << "Enter the IP address to connect to: ";
	cin >> ip;
	//转换ip
	unsigned long ip_addr = inet_addr(ip.c_str());
	if (ip_addr < 0)
	{
		cout << "Error: invalid IP address" << endl;
		return -1;
	}

	int cli_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (cli_sock < 0)
	{
		cout << "Error: create socket failed!" << endl;
		return -1;
	}

	struct sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(8888);
	sock_addr.sin_addr.s_addr = ip_addr;
	bzero(&(sock_addr.sin_zero), 8);

	socklen_t sa_size = sizeof(struct sockaddr_in);
	err = connect(cli_sock, (struct sockaddr *)&sock_addr, sa_size);
	if (err < 0)
	{
		cout << "Error: connect server " << ip_addr << " failed!" << endl;
		return -1;
	}

	char msg[MAX_BUFFSIXE];
	cout << "Begin send message..." << endl;
	while (1)
	{
		cout << "input some message: ";
		cin >> msg;

		err = send(cli_sock, msg, strlen(msg) + 1, 0);
		if (err == -1)
		{
			cout << "Error: send message failed!" << endl;
			return -1;
		}
		if (strcmp(msg, "quit") == 0)
		{
			break;
		}
	}
	close(cli_sock);

	exit(0);
}
