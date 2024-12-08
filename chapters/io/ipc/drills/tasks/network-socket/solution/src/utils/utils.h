/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef UTILS_H_
#define UTILS_H_ 1

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log/log.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ERR(assertion, call_description)				\
	do {								\
		if (assertion)						\
			log_error("%s: %s",				\
				call_description, strerror(errno));	\
	} while (0)

#define DIE(assertion, call_description)				\
	do {								\
		if (assertion)	{					\
			log_fatal("%s: %s",				\
				call_description, strerror(errno));	\
			exit(EXIT_FAILURE);				\
		}							\
	} while (0)

#ifdef __cplusplus
}
#endif

#endif  /* UTILS_H_ */
