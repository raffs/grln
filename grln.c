#define _GNU_SOURCE

#include "grln.h"
#include "hashmap.h"
#include "strlist.h"

#define COLOR_RESET "\e[0m"

static const char *COLOR_TABLE[] = {
	/* bright colors */
	"\e[1;31m",  /* red */
	"\e[1;32m",  /* green */
	"\e[1;33m",  /* yellow */
	"\e[1;34m",  /* blue */
	"\e[1;35m",  /* magenta */
	"\e[1;36m",  /* cyan */
	"\e[1;37m",  /* white */
	"\e[1;30m",  /* black */

	"\e[31m",  /* red */
	"\e[32m",  /* green */
	"\e[33m",  /* yellow */
	"\e[34m",  /* blue */
	"\e[35m",  /* magenta */
	"\e[36m",  /* cyan */
	"\e[37m",  /* white */
	"\e[30m",  /* black */

	COLOR_RESET, /* Default color */
};

#define COLOR_TABLE_LEN 16

/* number (pos) used to walk up into the color cycle, clockwise ;) */
static unsigned int color_clock = 0;

#define print_color(s, color) printf("%s%s%s", color, s, COLOR_RESET)

const char *get_color()
{
	const char *color = COLOR_TABLE[color_clock];

	color_clock = (color_clock + 1) % COLOR_TABLE_LEN;
	return color;
}



int run_version(void)
{
	printf("version v0.1.0");
	return 0;
}

int run_help(void)
{
	printf("usage: grln [-v | --version] [-h | --help]\n"
	       "\n"
	       "Coloring lines that belongs together.\n"
	       "\n"
	       "OPTIONS:\n"
	       "\n"
	       "    -v | --version:  display grln version\n"
	       "    -h | --help:     show this message\n"
	       "\n"
	       "EXAMPLES:\n"
	       "\n"
	       "    $ cat file | grln\n");
	return 0;
}

int run_grln()
{
	size_t len = 0;
	ssize_t read = 0;
	char *line = NULL;
	char *word = NULL;
	struct hashmap map;

	hashmap_init(&map);
	do {
		const char *color;
		struct hashmap_entry *entry;

		read = getline(&line, &len, stdin);
		if (read < 0)
			break;

		word = split_line(line, ' ');
		if (!word)
			continue; /* let's just skip for now */

		entry = hashmap_get(&map, word);
		if (!entry) {
			color = get_color();
			entry = hashmap_entry_init(word, color);
			hashmap_add(&map, entry);
		}

		print_color(line, (const char *)entry->data);

	} while (read > 0);

	hashmap_free(&map);
	free(line);
	return 0;
}

int main(int argc, char* argv[])
{
	static struct option long_options[] = {
		{"version", no_argument, 0, 'v'},
		{"help",    no_argument, 0, 'h'},
		{0,         0,           0,   0},
	};

	for (;;) {
		int option_index = 0;
		int c = getopt_long(argc, argv, "v", long_options, &option_index);
		if (c == -1)
			break;
		switch (c) {
		case 'h':
			return run_help();
		case 'v':
			return run_version();
		}
	}

	return run_grln();
}
