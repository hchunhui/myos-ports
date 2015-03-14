/*
 * Copyright (c) 1999 Herbert Xu <herbert@gondor.apana.org.au>
 * This file contains code for the times builtin.
 */

#include <sys/times.h>
#include <unistd.h>
#ifdef USE_GLIBC_STDIO
#include <stdio.h>
#else
#include "bltin.h"
#endif
#include "system.h"

int timescmd() {
	printf("TODO: times\n");
	return 0;
}
