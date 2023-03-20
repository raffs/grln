#include "grln.h"

void BUG(char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	printf("BUG: ");
	fprintf(stderr, fmt, ap);
	va_end(ap);
	exit(128);
}

void die(char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	exit(127);
}

void *xmalloc(size_t size)
{
	void *d = malloc(size);
	if (!d)
		die("OutOfMemory\n");

	return d;
}

void *xrealloc(void *ptr, size_t size)
{
	void *d = realloc(ptr, size);
	if (!d)
		die("OutOfMemory\n");

	return d;
}

void *xcalloc(size_t nmemb, size_t size)
{
	void *d = calloc(nmemb, size);
	if (!d)
		die("OutOfMemory\n");

	return d;
}
