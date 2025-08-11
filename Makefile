CC := gcc
CFLAGS := -Iinclude -Wall -Wextra -g

all: mini-shell

mini-shell: src/main.o src/shell.o src/parser.o src/utils.o src/execargs.o
	$(CC) $(CFLAGS) $^ -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@