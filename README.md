# Mini Shell

A simple Unix-like shell written in C for learning and experimentation.

## Project Structure

.
├── include/        # Header files
├── src/            # Source files
├── tests/          # Unit tests
├── Makefile
└── README.md


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
./build/test_builtins
```

## License

MIT License

---

This project is for educational purposes and demonstrates basic shell concepts and system programming in


