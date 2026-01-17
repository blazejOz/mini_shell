CC := gcc
CFLAGS := -Iinclude -Wall -Wextra -g

# --- Main Program Configuration ---
OBJ := src/main.o src/shell.o src/parser.o src/utils.o src/builtins.o
TARGET := mini-shell

# --- Test Configuration ---
TEST_DIR := build
TEST_BIN := $(TEST_DIR)/test_parser $(TEST_DIR)/test_builtins $(TEST_DIR)/test_execargs

# Default target
all: $(TARGET)

# Link the main executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Pattern rule for object files
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# --- Test Build Rules ---

$(TEST_DIR)/test_parser: tests/test_parser.c src/parser.c src/utils.c
	@mkdir -p $(TEST_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_DIR)/test_builtins: tests/test_builtins.c src/builtins.c src/utils.c
	@mkdir -p $(TEST_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# --- Test Execution Targets ---

# Run only parser tests: make test-parser
test-parser: $(TEST_DIR)/test_parser
	./$(TEST_DIR)/test_parser

# Run only builtin tests: make test-builtins
test-builtins: $(TEST_DIR)/test_builtins
	./$(TEST_DIR)/test_builtins

# Run only execarg tests: make test-execargs
test-execargs: $(TEST_DIR)/test_execargs
	./$(TEST_DIR)/test_execargs

# Run everything: make test-all or make check
test-all: $(TEST_BIN)
	@for test in $(TEST_BIN); do \
		echo "Running $$test..."; \
		./$$test || exit 1; \
	done

# Aliases
test: test-all
check: test-all

# Cleanup
clean:
	rm -rf src/*.o $(TARGET) $(TEST_DIR)

.PHONY: all clean test test-all test-parser test-builtins test-execargs check