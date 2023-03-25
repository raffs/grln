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
	        return NULL;

	return list->strs[index];
}

static char normalize(char c)
{
	if (isspace(c))
		return ' ';
	return c;
}

/*
 * Returns whether s1 and s2 are equal, returning 0 otherwise. The
 * values are normalized to compare any white-space char as equal
 */
static int str_isqual_norm(const char *s1, const char *s2, size_t n)
{
	int equals = 0;

	if (n < 0)
		return 0;

	for (int i = 0; i < n; i++) {
		char c1 = s1[i];
		char c2 = s2[i];

		if (normalize(c1) == normalize(c2))
			equals++;
	}

	return equals == n;
}

static char *strsub(const char *s, size_t start, size_t size)
{
	char *str;

	str = xmalloc(sizeof(char) * (size + 1));
	memset(str, 0, size + 1);
	memcpy(str, s + start, size);
	return str;
}

/*
 * Returns true if an string only contains white-space characters,
 * returns false; otherwise.
 */
static int is_blank(const char *s)
{
	for (int i = 0, n = strlen(s); i < n; i++) {
		if (!isspace(s[i]))
			return 0;
	}

	return 1;
}

struct strlist *strlist_split(char *s, const char *delim)
{
	struct strlist *terms = strlist_init(3);
	char *term = NULL;
	size_t len = strlen(s);
	size_t delim_len = strlen(delim);
	size_t last_word = 0;
	const char *next = s;

	if (delim_len > len)
		return NULL; /* it make no sense, otherwise. */

	for (int i = 0; i < len - delim_len; i++, next++) {
		if (!str_isqual_norm(next, delim, delim_len))
			continue;

		term = strsub(s, last_word, (i - last_word));
		if (!is_blank(term))
			strlist_add(terms, term);

		i += (delim_len - 1);
		last_word = i;
		next += (delim_len - 1);
	}

	/* take the rest of the string, minus the `\n` */
	term = strsub(s, last_word , len - last_word);
	strlist_add(terms, term);

	return terms;
}
