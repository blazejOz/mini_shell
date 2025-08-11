#ifndef COMMAND_H
#define COMMAND_H
#include <stddef.h>

typedef struct {
    char **argv;
    int argc;
    int capacity;
} ExecArgs;

void execargs_init(ExecArgs *ea);
int  execargs_push(ExecArgs *ea, const char *token);  // strdup-like copy inside
int  execargs_finalize(ExecArgs *ea);                 // ensure argv[argc] == NULL
void execargs_free(ExecArgs *ea);


#endif