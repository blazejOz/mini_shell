CC := gcc
CFLAGS := -Iinclude -Wall -Wextra -g

all: mini-shell

mini-shell: src/main.o src/shell.o
	$(CC) $(CFLAGS) $^ -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f src/*.o mini-shell