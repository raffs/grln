#ifndef _GRLN_HASHMAP_H
#define _GRLN_HASHMAP_H

struct hashmap_entry {
	void *data;

	struct hashmap_entry *next;
	unsigned int hash;
};

/*
 * Provides a hash-like structure to keep the words and its color.
 */
struct hashmap {
	struct hashmap_entry **table;

	unsigned int size;
};

void hashmap_init(struct hashmap *map);
void hashmap_free(struct hashmap *map);
unsigned int strhash(const char *str);
struct hashmap_entry *hashmap_entry_init(const char *key, const char *value);

/*
 * Add a new entry into the hashmap, appending to a bucket in case the value
 * already exists.
 */
void hashmap_add(struct hashmap *map, struct hashmap_entry *entry);

/*
 * Get an entry from the hashmap *map or NULL if the entry doesn't exists.
 */
struct hashmap_entry *hashmap_get(struct hashmap *map, const char *key);

#endif
