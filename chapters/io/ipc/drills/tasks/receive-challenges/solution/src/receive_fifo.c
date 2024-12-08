// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "utils/utils.h"

static const char fifo_path[] = "apollodorus";

#ifndef BUFSIZ
#define BUFSIZ		256
#endif

// Read exactly `size` bytes from file descriptor `fd` into buffer `buf`,
// or until EOF is reached.
size_t rread(int fd, void *buf, size_t size)
{
	int bytes_read = 0;
	size_t total_bytes_read = 0;

	while (true) {
		bytes_read = read(fd, buf, size);
		DIE(bytes_read < 0, "read");

		if (bytes_read == 0)
			break;

		total_bytes_read += bytes_read;
		if (total_bytes_read == size)
			break;
	}

	return total_bytes_read;
}

int main(void)
{
	int rc, fd;
	char buffer[BUFSIZ];

	/**
	 * Create FIFO if it doesn't exist or if it exists and has incorrect
	 * permissions.
	 */
	rc = access(fifo_path, R_OK | W_OK);
	if (rc < 0) {
		/* TODO 2: `access()` failed so you need to create the FIFO */
		rc = mkfifo(fifo_path, 0666);
		DIE(rc < 0, "mkfifo");
	}

	/* TODO 2: Open FIFO for reading. */
	fd = open(fifo_path, O_RDONLY);
	DIE(fd < 0, "open");

	/* TODO 2: Read flag from FIFO. */
	rc = rread(fd, buffer, BUFSIZ);
	DIE(rc < 0, "rread");

	printf("Flag is: %s\n", buffer);

	return 0;
}
