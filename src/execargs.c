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

static int ensure_capacity(ExecArgs *ea){
    //allocate memory
    if (ea->capacity == 0){
        int new_capacity = 4;
        char **tmp = calloc(new_capacity, sizeof(*ea->argv));
        if(tmp == NULL){
            printf("error allocating memory");
            return -1;
        }   
        ea->argv = tmp;
        ea->capacity = new_capacity; 
        return 0;
    }
    //reallocate memory when more arguments 
    if(ea->argc == ea->capacity){
        int new_capacity = ea->capacity * 2;
        char **new_argv = realloc(ea->argv, new_capacity * sizeof(*ea->argv));
        if(new_argv == NULL){
            printf("error reallocating memory");
            return -1;
        }        
        ea->argv = new_argv;
        ea->capacity = new_capacity;
        return 0;
    }
    return 0;
}

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
        ea->argc = 0;
        ea->capacity = 0;
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
