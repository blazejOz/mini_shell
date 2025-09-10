CC := gcc
CFLAGS := -Iinclude -Wall -Wextra -g

# --- main program ---
all: mini-shell

mini-shell: src/main.o src/shell.o src/parser.o src/utils.o src/execargs.o
	$(CC) $(CFLAGS) $^ -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- test support ---
build:
	mkdir -p build

build/test_execargs: build tests/test_execargs.c src/execargs.c src/utils.c
	$(CC) $(CFLAGS) $^ -o $@

build/test_parser: build tests/test_parser.c src/parser.c src/utils.c
	$(CC) $(CFLAGS) $^ -o $@

TEST_BIN := build/test_execargs build/test_parser

test: $(TEST_BIN)

check: test
	./build/test_execargs
	./build/test_parser

clean:
	rm -f src/*.o mini-shell $(TEST_BIN)
