TARGET = grln

SRCS = grln.c
SRCS += wrappers.c
SRCS += hashmap.c

CFLAGS = -g -O3 -Wall -std=c11

OBJS = $(SRCS:.c=.o)

VALGRIND_FLAGS = --track-origins=yes --leak-check=full

.PHONY: test clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

memcheck:
	echo "hello world" | valgrind $(VALGRIND_FLAGS) ./$(TARGET)

test:
	(cd t; ./t*.sh)

install:
	install -o root -g root -m 0755 ./$(TARGET) /usr/local/bin/$(TARGET)

uninstall:
	rm -f /usr/local/bin/$(TARGET)

clean:
	rm -f ./$(TARGET)
	rm -f *.o *.a
