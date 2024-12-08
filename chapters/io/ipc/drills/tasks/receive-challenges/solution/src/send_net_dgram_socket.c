// SPDX-License-Identifier: BSD-3-Clause
/* File used for testing receive_net_dgram_socket.c. Do not edit. */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "utils/utils.h"

unsigned short remote_port = 4242;
static const char FLAG[] = "SO{look_at_all_the_pretty_lights}";

int main(void)
{
	int rc;
	int fd;
	struct sockaddr_in raddr;

	/* Create socket. */
	fd = socket(PF_INET, SOCK_DGRAM, 0);
	DIE(fd < 0, "socket");

	/* Define remote address. */
	memset(&raddr, 0, sizeof(raddr));
	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(remote_port);
	raddr.sin_addr.s_addr = htonl(INADDR_ANY);

	/* Write flag to socket. */
	rc = sendto(fd, FLAG, sizeof(FLAG), 0, (struct sockaddr *) &raddr, sizeof(raddr));
	DIE(rc < 0, "sendto");

	close(fd);

	return 0;
}
