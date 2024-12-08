// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "utils/utils.h"

#ifndef BUFSIZ
#define BUFSIZ		256
#endif

static char *argv[] = { "./send_fd_14", NULL };  // args for execve()

int main(void)
{
	int pipefd[2];
	char buf[BUFSIZ];
	int rc, pid;

	/**
	 * The `./send_fd_14` binary writes the flag to the file descriptor 14.
	 * We will create a pipe whose write end is on file descriptor 14, then
	 * we will create the child process. We will get the flag from the read
	 * end of the pipe.
	 */

	/* TODO 2: Create a pipe. */
	rc = pipe(pipefd);
	DIE(rc < 0, "pipe");

	log_info("Created pipe with descriptors %d and %d.\n", pipefd[0],
		pipefd[1]);

	/* TODO 2: Create the child process. */
	pid = fork();
	DIE(pid < 0, "fork");

	if (pid == 0) { /* Child process */
		/* TODO 2: Redirect the write end of the pipe `pipefd[1]` to fd 14. */
		rc = dup2(pipefd[1], 14);
		DIE(rc < 0, "dup2");

		/* TODO 2: Run the `./send_fd_14` binary. */
		rc = execve("./send_fd_14", argv, NULL);
		DIE(rc < 0, "execve");
		/* Never reached. */
	}

	/* TODO 2: Read the flag from the read end of the pipe `pipefd[0]`. */
	rc = read(pipefd[0], buf, BUFSIZ);
	DIE(rc < 0, "read");

	printf("Flag is: %s\n", buf);

	/* Wait for child process. */
	wait(NULL);

	return 0;
}
