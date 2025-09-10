CC := gcc
CFLAGS := -Iinclude -Wall -Wextra -g

# --- main program ---
all: mini-shell

mini-shell: src/main.o src/shell.o src/parser.o src/utils.o src/execargs.o
	$(CC) $(CFLAGS) $^ -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- test support ---

build/test_execargs: tests/test_execargs.c src/execargs.c src/utils.c
	mkdir -p build
	$(CC) $(CFLAGS) $^ -o $@

build/test_parser: tests/test_parser.c src/parser.c src/utils.c
	mkdir -p build
	$(CC) $(CFLAGS) $^ -o $@


TEST_BIN := build/test_execargs build/test_parser

test: $(TEST_BIN)

check: test
	./build/test_execargs
	./build/test_parser

clean:
	rm -f src/*.o mini-shell $(TEST_BIN)
