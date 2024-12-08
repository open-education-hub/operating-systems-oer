// SPDX-License-Identifier: BSD-3-Clause
/* File used for testing receive_pipe.c. Do not edit. */

#include <unistd.h>
#include "utils/utils.h"

static const char FLAG[] = "SO{in_the_pipe_five_by_five}\n";

int main(void)
{
	write(14, FLAG, sizeof(FLAG));
	return 0;
}
