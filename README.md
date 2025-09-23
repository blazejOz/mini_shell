# Mini Shell

A simple Unix-like shell written in C for learning and experimentation.

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
./build/mini_shell
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
│   └── test_execargs.c
├── Makefile            # Build instructions
└── README.md           # Project documentation
```

## Features

- Interactive shell prompt
- Command parsing and tokenization
- Built-in commands:
  - `exit` — exit the shell (optionally with a status code)
  - `pwd` — print the current working directory
  - `cd` — change the current directory
  - `echo` — print arguments to standard output
- Basic error handling for invalid usage

## Planned Features

- Running external programs (`exec`)
- I/O redirection (`>`, `<`)
- Pipes (`|`)
- Environment variable expansion (`$VAR`)
- Command history

## Building

```bash
make
```

## Running

```bash
./build/mini_shell
```

## Testing

```bash
make test
make check
```

## License

MIT License

---

This project is for educational purposes and demonstrates basic shell concepts and system programming in C.