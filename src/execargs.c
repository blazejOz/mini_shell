#include "execargs.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

/*
typedef struct {
    char **argv;
    int argc;
    int capacity;
} ExecArgs;
*/

static int ensure_capacity(ExecArgs *ea){
    //allocate memory
    if (ea->capacity == 0){
        int new_capacity = 4;
        char **tmp = calloc(new_capacity, sizeof(*ea->argv));
        if(tmp == NULL) return -1;  

        ea->argv = tmp;
        ea->capacity = new_capacity; 
        return 1;
    }
    //reallocate memory when more arguments 
    if(ea->argc == ea->capacity){
        int new_capacity = ea->capacity * 2;
        char **new_argv = realloc(ea->argv, new_capacity * sizeof(*ea->argv));
        if(new_argv == NULL) return -1;
           
        ea->argv = new_argv;
        ea->capacity = new_capacity;
        return 1;
    }
    return 1;
}

void execargs_init(ExecArgs *ea){
    ea->argv = NULL;
    ea->argc = 0;
    ea->capacity = 0;
}

int execargs_push(ExecArgs *ea, const char *token) {
    if(ensure_capacity(ea)){
        ea->argv[ea->argc] = c_string_duplication(token);
        ea->argc += 1;
        return 1;
    }
    return -1;
}

int execargs_finalize(ExecArgs *ea) {             
    ea->argv[ea->argc] = NULL;

}


void execargs_free(ExecArgs *ea) {
    if (ea->argv == NULL) {
        ea->argc = 0;
        ea->capacity = 0;
    }
    for (int i = 0; i < ea->argc; ++i) {
        free(ea->argv[i]);
    }
    free(ea->argv);
    ea->argv = NULL;
    ea->argc = 0;
    ea->capacity = 0;
}
