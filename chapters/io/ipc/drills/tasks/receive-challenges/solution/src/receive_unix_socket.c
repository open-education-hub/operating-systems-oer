// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <sys/socket.h>

#include "utils/utils.h"

#ifndef BUFSIZ
#define BUFSIZ		256
#endif

static const char socket_path[] = "golden_gate";

/**
 * Create a sockaddr_un structure with family AF_UNIX and the given path.
 */
struct sockaddr_un get_sockaddr(const char *path)
{
	struct sockaddr_un addr;

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	snprintf(addr.sun_path, strlen(path) + 1, "%s", path);

	return addr;
}

int main(void)
{
	int rc;
	int listenfd, connectfd;
	struct sockaddr_un addr = get_sockaddr(socket_path);
	char buffer[BUFSIZ];

	/* TODO 2: Remove socket_path. */
	rc = unlink(socket_path);
	DIE(rc < 0 && errno != ENOENT, "unlink");

	/* TODO 2: Create a Unix domain socket for stream communication. */
	listenfd = socket(PF_UNIX, SOCK_STREAM, 0);
	DIE(listenfd < 0, "socket");

	/* TODO 2: Bind socket to path. */
	rc = bind(listenfd, (struct sockaddr *) &addr, sizeof(addr));
	DIE(rc < 0, "bind");

	/* TODO 2: Listen for incoming connections. */
	rc = listen(listenfd, 10);
	DIE(rc < 0, "listen");

	/* TODO 2: Accept a connection. */
	connectfd = accept(listenfd, NULL, NULL);
	DIE(connectfd < 0, "accept");

	/* TODO 2: Read flag from socket. */
	rc = read(connectfd, buffer, BUFSIZ);
	DIE(rc < 0, "read");

	printf("Flag is: %s\n", buffer);

	/* TODO 4: Close the sockets. */
	rc = close(connectfd);
	DIE(rc < 0, "close");
	rc = close(listenfd);
	DIE(rc < 0, "close");

	return 0;
}
