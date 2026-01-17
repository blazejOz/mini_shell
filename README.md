# Mini Shell

A simple Unix-like shell written in C for learning and experimentation.

![Mini-Shell Demo](assets/demo.gif)

## Prerequisites
- Linux or macOS with a POSIX userland
- `gcc` or `clang`
- `make`
- C standard: C17; uses POSIX.1-2008 APIs

## Quickstart

```bash
git clone https://github.com/blazejOz/mini_shell mini_shell
cd mini_shell
make
./mini_shell
```

## Project Structure

```
mini_shell/
├── src/                # Source code files
│   ├── main.c          # Entry point of the shell
│   ├── shell.c         # Shell loop and command execution
│   ├── builtins.c      # Implementation of built-in commands
│   ├── parser.c        # Command parsing and tokenization
│   └── utils.c         # Utility functions
├── include/            # Header files
│   ├── shell.h
│   ├── builtins.h
│   ├── parser.h
│   └── utils.h
├── tests/              # Test files
│   ├── test_builtins.c
│   ├── test_parser.c
├── Makefile            # Build instructions
└── README.md           # Project documentation
```

## Features

- **Interactive Shell Loop:** Robust REPL (Read-Eval-Print Loop) with a clean prompt.
- **Advanced Command Pipeline:** Supports chaining multiple commands using the `|` operator. 
  - Efficiently handles $N$ processes with $N-1$ concurrent pipes.
  - Proper file descriptor management (uses `dup2` for I/O redirection between stages).
  - Synchronous execution: The shell waits for the entire pipeline to complete before returning to the prompt.
- **Intelligent Command Dispatcher:**
  - **Built-in Commands:** Executed directly in the parent process (`cd`, `exit`, `pwd`, `echo`).
  - **External Binaries:** Discovered via `$PATH` and executed in forked subshells using `execvp`.
- **Memory Safety:** Implements a multi-level cleanup strategy to ensure no memory leaks during parsing or execution.

## Roadmap & Planned Features

- [x] **Process Pipelines:** Concurrent execution of piped commands.
- [x] **External Execution:** Full integration with system binaries via `exec`.
- [ ] **I/O Redirection:** Implementing file descriptor hijacking for `>`, `>>`, and `<`.
- [ ] **Signal Handling:** Graceful management of `Ctrl+C` (SIGINT) and `Ctrl+Z` (SIGTSTP).
- [ ] **Variable Expansion:** Support for `$HOME`, `$USER`, and local shell variables.
- [ ] **Persistence:** Command history saved to `~/.mini_shell_history`.

## Building

```bash
make
```

## Running

```bash
./mini_shell
```

## Testing

```bash
make test
```

## License

MIT License

---

This project is for educational purposes and demonstrates basic shell concepts and system programming in C.
