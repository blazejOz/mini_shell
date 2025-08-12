#include "execargs.h"
#include <stdlib.h>
#include <string.h>

/*
typedef struct {
    char **argv;
    int argc;
    int capacity;
} ExecArgs;
*/

void execargs_init(ExecArgs *ea){
    ea->argv = NULL;
    ea->argc = 0;
    ea->capacity = 0;
}


int execargs_push(ExecArgs *ea, const char *token) {  

}

int execargs_finalize(ExecArgs *ea) {             
  
}


void execargs_free(ExecArgs *ea) {
    if (ea->argv == NULL) {
        return;
    }
    for (int i = 0; i < ea->argc; ++i) {
        free(ea->argv[i]);
    }
    free(ea->argv);
    ea->argv = NULL;
    ea->argc = 0;
    ea->capacity = 0;
}
