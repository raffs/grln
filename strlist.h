#ifndef _GRLN_STRLIST_H
#define _GRLN_STRLIST_H

struct strlist {
	char **strs;

	int length;
	int grow_in;
	int alloc;
};

struct strlist *strlist_init(int prealloc);

void strlist_free(struct strlist *list);

void strlist_add(struct strlist *list, char *str);

char *strlist_get(struct strlist *list, int index);

/*
 * Split a the string `s` into n sub-strings, using `delim` as the
 * splitted character.
 */
struct strlist *strlist_split(char *s, const char *delim);

#endif
