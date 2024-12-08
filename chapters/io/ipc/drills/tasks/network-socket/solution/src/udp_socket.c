// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "utils/utils.h"

#ifndef BUFSIZ
#define BUFSIZ		256
#endif

static const char IP[] = "127.0.0.1";
static const int PORT = 5000;

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

static void receiver_loop(void)
{
	struct sockaddr_in addr = get_sockaddr(IP, PORT);
	char output[BUFSIZ];
	int listenfd;
	int rc;

	/* TODO 2: Create a network socket with SOCK_STREAM type. */
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);
	DIE(listenfd < 0, "socket");

	/* TODO 2: Bind the socket to the addr. */
	rc = bind(listenfd, (struct sockaddr *) &addr, sizeof(addr));
	DIE(rc < 0, "bind");

	while (1) {
		memset(output, 0, BUFSIZ);

		/* TODO 2: Receive data from the connected socket */
		rc = recvfrom(listenfd, output, BUFSIZ, 0, NULL, NULL);
		DIE(rc < 0, "recv");

		if (strcmp(output, "exit") == 0)
			break;

		printf("[Receiver]: %s\n", output);
		fflush(stdout);
	}

	/* TODO 2: Close listenfd. */
	rc = close(listenfd);
	DIE(rc < 0, "close");
}

static void sender_loop(void)
{
	struct sockaddr_in addr = get_sockaddr(IP, PORT);
	char input[BUFSIZ];
	int sockfd;
	int rc;

	/* TODO 2: Create a network socket with SOCK_STREAM type. */
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	DIE(sockfd < 0, "socket");

	while (1) {
		memset(input, 0, BUFSIZ);
		fgets(input, BUFSIZ, stdin);
		// Remove trailing newline
		if (input[strlen(input) - 1] == '\n')
			input[strlen(input) - 1] = '\0';

		printf("[Sender]: %s\n", input);

		/* TODO 2: Send input to socket. */
		rc = sendto(sockfd, input, strlen(input), 0, (struct sockaddr *) &addr, sizeof(addr));
		DIE(rc < 0, "send");

		if ((strcmp(input, "exit") == 0 || strlen(input) == 0))
			break;
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
