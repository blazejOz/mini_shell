CC := gcc
CFLAGS := -Iinclude -Wall -Wextra -g

all: mini-shell

mini-shell: src/main.o src/shell.o src/parser.o src/utils.o src/execargs.o
	$(CC) $(CFLAGS) $^ -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- test support ---
TEST_SRC := tests/test_execargs.c src/execargs.c src/utils.c
TEST_BIN := build/test_execargs

test: $(TEST_BIN)

$(TEST_BIN): $(TEST_SRC)
	$(CC) $(CFLAGS) $^ -o $@

check: test
	./$(TEST_BIN)

clean:
	rm -f src/*.o mini-shell $(TEST_BIN)
