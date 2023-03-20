#include "grln.h"
#include "strlist.h"

struct strlist *strlist_init(int prealloc)
{
	struct strlist *strl = NULL;

	if (prealloc < 0)
		BUG("strlist: prealloc should not be negative, value: %d\n", prealloc);

	strl = xmalloc(sizeof(struct strlist));
	strl->length = 0;
	strl->alloc = prealloc;
	strl->grow_in = prealloc;
	strl->strs = xmalloc(sizeof(char *) * prealloc);

	return strl;
}

void strlist_free(struct strlist *list)
{
	free(list->strs);
}

void strlist_add(struct strlist *list, char *str)
{
	/* should the list grow? */
	if (list->length == list->alloc) {
		list->alloc += list->grow_in;
		list->strs = xrealloc(list->strs, sizeof(char *) * list->alloc);
	}

	list->strs[list->length++] = str;
}

char *strlist_get(struct strlist *list, int index)
{
	if (index >= list->length)
		BUG("strlist_get: Out of bound array access");

	return list->strs[index];
}

/*
 * Normalize character returned the "normalized" version of the given
 * character, in case it has one.
 *
 *  return ' ', for any white-space characters, i.e. \t, \b, ' ', etc..
 */
static char normalize(char c)
{
	if (isspace(c))
		return ' ';
	return c;
}

struct strlist *strlist_split(char *s, int delim)
{
	struct strlist *terms = strlist_init(3);
	char *term = NULL;
	int term_init = 0;
	int word_started = 0;
	size_t term_size = 0;

	for (int i = 0, n = strlen(s); i < n; i++) {
		char c = s[i];

		if (!word_started && normalize(c) == delim) {
			term_init = i + 1;
			continue;
		}
		word_started = 1;

		if (normalize(c) == delim) {
			/* read back now that we found a column */
			term_size = i - term_init;
			term = xcalloc(1, sizeof(char) * term_size + 1);
			memcpy(term, s + term_init, term_size);
			term[term_size + 1] = '\0';

			/* preparing for the next round */
			word_started = 0;
			term_init = i;
			strlist_add(terms, term);
		}
	}

	return terms;
}
