# mini_shell

include/ vs src/

    Public headers in include/ let different parts of your project (and tests) share interfaces without circular dependencies.

    Implementation lives in src/, keeping things tidy.

builtins/

    Treat built-in commands (like cd, echo, exit) as separate compilation units.

    You can even compile them into a static library (libbuiltins.a) and link it into your shell.

Separation of concerns

    parser.c only knows about tokenizing and building a simple AST or command structure.

    executor.c decides whether something is a builtin or a system program, handles forking, wait, redirection, pipelines, etc.

utils.c / utils.h

    Put reusable helpers—string splitting, memory wrappers, error-reporting—here so you don’t duplicate code.

tests/

    As your parser and executor logic grows, you’ll want automated checks. CUnit, Unity, or just simple assert-based tests can go here.

Makefile hierarchy

    A top-level Makefile that builds the shell binary, and small Makefiles in subdirectories if you get fancy (e.g. building builtins as a library).

Documentation

    Keep your design decisions, supported features, and “to implement” list in docs/.