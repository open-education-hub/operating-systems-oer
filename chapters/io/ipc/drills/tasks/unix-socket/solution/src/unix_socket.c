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

static const char socket_path[] = "my-socket";

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

static void receiver_loop(void)
{
	struct sockaddr_un addr = get_sockaddr(socket_path);
	char output[BUFSIZ];
	int listenfd, connectfd;
	int rc;

	/* Recreate the socket for each communication. */
	remove(socket_path);

	/* TODO 2: Create a UNIX socket with SOCK_STREAM type. */
	listenfd = socket(PF_UNIX, SOCK_STREAM, 0);
	DIE(listenfd < 0, "socket");

	/* TODO 2: Bind the socket to the addr. */
	rc = bind(listenfd, (struct sockaddr *) &addr, sizeof(addr));
	DIE(rc < 0, "bind");

	/* TODO 2: Mark socket as passive socket using listen(). */
	rc = listen(listenfd, 1);
	DIE(rc < 0, "listen");

	/* TODO 2: Use accept() to get the socket for a new connection. */
	connectfd = accept(listenfd, NULL, NULL);
	DIE(connectfd < 0, "accept");

	while (1) {
		memset(output, 0, BUFSIZ);
		/* TODO 2: Receive data from the connected socket */
		rc = recv(connectfd, output, sizeof(output), 0);
		DIE(rc < 0, "recv");

		if (rc == 0)
			break;

		printf("[Receiver]: %s\n", output);
		fflush(stdout);
	}

	/* TODO 4: Close connectfd and listenfd. */
	rc = close(connectfd);
	DIE(rc < 0, "close");
	rc = close(listenfd);
	DIE(rc < 0, "close");
}

static void sender_loop(void)
{
	struct sockaddr_un addr = get_sockaddr(socket_path);
	char input[BUFSIZ];
	int sockfd;
	int rc;

	/* TODO 2: Check if socket exists. Hint: access(). */
	rc = access(socket_path, R_OK | W_OK);
	DIE(rc < 0, "access");

	/* TODO 2: Create a UNIX socket with SOCK_STREAM type. */
	sockfd = socket(PF_UNIX, SOCK_STREAM, 0);
	DIE(sockfd < 0, "socket");

	/* TODO 2: Connect to the socket. */
	rc = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
	DIE(rc < 0, "connect");

	while (1) {
		memset(input, 0, BUFSIZ);
		fgets(input, BUFSIZ, stdin);
		// Remove trailing newline
		if (input[strlen(input) - 1] == '\n')
			input[strlen(input) - 1] = '\0';

		printf("[Sender]: %s\n", input);
		if ((strcmp(input, "exit") == 0 || strlen(input) == 0))
			break;

		/* TODO 2: Send input to socket. */
		rc = send(sockfd, input, strlen(input), 0);
		DIE(rc < 0, "send");
	}

	/* TODO 2: Close socket. */
	rc = close(sockfd);
	DIE(rc < 0, "close");
}

/**
 * Simulate a sender-receiver communication using a named pipe.
 * Run the program as a receiver by default, or as a sender if the -s or --sender.
 */
int main(int argc, char *argv[])
{
	if (argc == 1) {  // Run as receiver by default
		receiver_loop();
	} else if (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--sender") == 0) {
		sender_loop();
	} else {
		fprintf(stderr, "Usage: %s [-s|--sender]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	return 0;
}
