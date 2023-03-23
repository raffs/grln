#include "grln.h"
#include "hashmap.h"

#define HASHMAP_INITIAL_SIZE 64

#define FNV32_BASE ((unsigned int) 0x811c9dc5)
#define FNV32_PRIME ((unsigned int) 0x01000193)

void hashmap_init(struct hashmap *map)
{
	memset(map, 0, sizeof(*map));

	if (!map->table)
		map->table = xmalloc(sizeof(struct hashmap_entry) * HASHMAP_INITIAL_SIZE);

	map->size = HASHMAP_INITIAL_SIZE;
}

void hashmap_free(struct hashmap *map)
{
	if (!map)
		return;
	/* yeah, yeah; we are not free'ing the buckets and its entries. */
	free(map->table);
}

/* A lot of this code is inspired from Git's hashmap.c source code :) */
unsigned int strhash(const char *str)
{
	unsigned int c;
	unsigned int hash = FNV32_BASE;

	while ((c = *str++))
		hash = (hash * FNV32_PRIME) ^ c;

	return hash;
}

struct hashmap_entry *hashmap_entry_init(const char *key, const char *value)
{
	struct hashmap_entry *entry;
	unsigned int hash = strhash(key);
	size_t len = strlen(value);

	entry = xmalloc(sizeof(*entry));
	memset(entry, 0, sizeof(*entry));

	/* compute hash */
	entry->hash = hash;
	entry->data = xmalloc(sizeof(char) * len);
	memcpy(entry->data, value, strlen(value));
	entry->next = NULL;

	return entry;
}

static inline unsigned int hashmap_bucket(const struct hashmap *map, unsigned int hash)
{
	return hash & (map->size - 1);
}

void hashmap_add(struct hashmap *map, struct hashmap_entry *entry)
{
	unsigned int b = hashmap_bucket(map, entry->hash);

        entry->next = map->table[b];
	map->table[b] = entry;
}

struct hashmap_entry *hashmap_get(struct hashmap *map, const char *key)
{
	struct hashmap_entry *e;
	unsigned int hash = strhash(key);
	unsigned int b = hashmap_bucket(map, hash);

	if (!map->table[b])
		return NULL;

	for (e = map->table[b]; e; e = e->next) {
		if (e->hash == hash)
			return e;
	}

	return NULL;
}
