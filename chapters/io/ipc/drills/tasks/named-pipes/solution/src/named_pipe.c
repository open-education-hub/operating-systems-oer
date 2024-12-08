// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "utils/utils.h"

static const char fifo_path[] = "my-fifo";

#ifndef BUFSIZ
#define BUFSIZ		256
#endif

void create_fifo_if_needed(void)
{
	/* TODO 9: Use access() to check if the FIFO exists and has the right permissions.
	 * If it exists but has the wrong permissions, delete it using unlink().
	 * If it doesn't exist create it using mkfifo().
	 */
	int rc = access(fifo_path, R_OK | W_OK);

	if (rc < 0) {
		rc = unlink(fifo_path);

		rc = mkfifo(fifo_path, 0666);
		DIE(rc < 0, "mkfifo");
	}
}

static void receiver_loop(void)
{
	char output[BUFSIZ];
	int fd, rc;

	/* TODO 4: Create FIFO if it does not exist, then open it for reading. */
	create_fifo_if_needed();

	fd = open(fifo_path, O_RDONLY);
	DIE(fd < 0, "open");

	while (1) {
		/* TODO 5: Read until EOF. */
		rc = read(fd, output, BUFSIZ);
		DIE(rc < 0, "read");

		if (rc == 0)
			break;

		printf("[Receiver]: %s\n", output);
		fflush(stdout);
	}

	/* TODO 2: Close FIFO. */
	rc = close(fd);
	DIE(rc < 0, "close");
}

static void sender_loop(void)
{
	char input[BUFSIZ];
	int fd, rc;

	/* TODO 4: Create FIFO if it does not exist, then open it for writing. */
	create_fifo_if_needed();

	fd = open(fifo_path, O_WRONLY);
	DIE(fd < 0, "open");

	while (1) {
		memset(input, 0, BUFSIZ);
		fgets(input, BUFSIZ, stdin);
		// Remove trailing newline
		if (input[strlen(input) - 1] == '\n')
			input[strlen(input) - 1] = '\0';

		if ((strcmp(input, "exit") == 0 || strlen(input) == 0))
			break;

		/* TODO 2: Write to FIFO. */
		rc = write(fd, input, BUFSIZ);
		DIE(rc < 0, "write");
	}

	/* TODO 2: Close FIFO. */
	rc = close(fd);
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
