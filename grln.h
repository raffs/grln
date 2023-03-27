#ifndef _GRLN_H
#define _GRLN_H

#define _GNU_SOURCE

#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

/* dealing with erros and BUG */
void BUG(char *fmt, ...);
void die(char *fmt, ...);

/* dealing with memory allocation */
void *xmalloc(size_t size);
void *xrealloc(void *ptr, size_t size);
void *xcalloc(size_t nmemb, size_t size);

/* dealing with number conversions */
long xstrtol(const char *nptr, char **endptr, int base);

#endif
