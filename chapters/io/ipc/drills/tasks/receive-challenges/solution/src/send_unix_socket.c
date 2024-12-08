// SPDX-License-Identifier: BSD-3-Clause
/* File used for testing receive_unix_socket.c. Do not edit. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <sys/socket.h>

#include "utils/utils.h"

static const char socket_path[] = "golden_gate";
static const char FLAG[] = "SO{cold_is_the_void}";

int main(void)
{
	int rc;
	int fd;
	struct sockaddr_un addr;

	/* UNIX socket must exist. It must be created by receiver. */
	rc = access(socket_path, R_OK | W_OK);
	DIE(rc < 0, "access");

	/* Create socket. */
	fd = socket(PF_UNIX, SOCK_STREAM, 0);
	DIE(fd < 0, "open");

	/* Connect socket to server. */
	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	snprintf(addr.sun_path, sizeof(socket_path), "%s", socket_path);
	rc = connect(fd, (struct sockaddr *) &addr, sizeof(addr));
	DIE(rc < 0, "connect");

	/* Write flag to socket. */
	rc = write(fd, FLAG, sizeof(FLAG));
	DIE(rc < 0, "write");

	close(fd);

	return 0;
}
