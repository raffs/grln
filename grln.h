#ifndef _GRLN_H
#define _GRLN_H

#define _GNU_SOURCE

#include <getopt.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* dealing with erros and BUG */
void BUG(char *fmt, ...);
void die(char *fmt, ...);

/* dealing with memory allocation */
void *xmalloc(size_t size);

#endif
