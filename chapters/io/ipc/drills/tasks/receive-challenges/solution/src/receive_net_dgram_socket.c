// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "utils/utils.h"

#ifndef BUFSIZ
#define BUFSIZ		256
#endif

static const char IP[] = "127.0.0.1";
static unsigned short port = 4242;

/**
 * Create a sockaddr_in structure with the given IP and port.
 */
struct sockaddr_in get_sockaddr(const char *ip, const int port)
{
	struct sockaddr_in addr;

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);

	return addr;
}

int main(void)
{
	int fd, rc;
	struct sockaddr_in addr = get_sockaddr(IP, port);
	char buffer[BUFSIZ];

	/* TODO 2: Create a socket for datagram communication. */
	fd = socket(PF_INET, SOCK_DGRAM, 0);
	DIE(fd < 0, "socket");

	/* TODO 2: Bind socket to address. */
	rc = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
	DIE(rc < 0, "bind");

	/* TODO 2: Read flag from socket. */
	rc = recvfrom(fd, buffer, BUFSIZ, 0, NULL, NULL);
	DIE(rc < 0, "recvfrom");

	printf("Flag is: %s\n", buffer);

	/* TODO 2: Close socket. */
	rc = close(fd);
	DIE(rc < 0, "close");

	return 0;
}
