#ifndef BUILTINS_H
#define BUILTINS_H

typedef enum {
    BUILTIN_NONE = 0,
    BUILTIN_EXIT,
    BUILTIN_CD,
    BUILTIN_PWD,
    BUILTIN_ECHO
}BuiltinType;

BuiltinType builtin_match(const char *cmd);

int builtin_run(BuiltinType which, char **args, int *should_exit, int *exit_status);

#endif