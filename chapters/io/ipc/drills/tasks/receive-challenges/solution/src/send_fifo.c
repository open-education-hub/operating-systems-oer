// SPDX-License-Identifier: BSD-3-Clause
/* File used for testing receive_fifo.c. Do not edit. */

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "utils/utils.h"

static const char fifo_path[] = "apollodorus";
static const char FLAG[] = "SO{one_man_enter_two_men_leave}";

int main(void)
{
	int rc;
	int fd;

	/* FIFO must exist. It must be created by receiver. */
	rc = access(fifo_path, R_OK | W_OK);
	DIE(rc < 0, "access");

	/* Open FIFO. */
	fd = open(fifo_path, O_RDWR);
	DIE(fd < 0, "open");

	/* Write flag to FIFO. */
	rc = write(fd, FLAG, sizeof(FLAG));
	DIE(rc < 0, "write");

	return 0;
}
