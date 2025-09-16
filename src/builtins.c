#include "builtins.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

BuiltinType builtin_match(const char *cmd){
    if (cmd == NULL || *cmd == '\0') return BUILTIN_NONE;
    if (strcmp(cmd, "exit") == 0) return BUILTIN_EXIT;
    if (strcmp(cmd, "pwd") == 0) return BUILTIN_PWD;
    if (strcmp(cmd, "cd") == 0) return BUILTIN_CD; 
    return BUILTIN_NONE;
}


static int bi_exit(int argc, char **argv, int *should_exit, int *exit_status);
static int bi_cd(int argc, char **argv);
static int bi_pwd(int argc, char **argv);
static int bi_echo(int argc, char **argv);

int builtin_run(BuiltinType which, int argc, char **argv,
                int *should_exit, int *exit_status) {
    switch (which) {
        case BUILTIN_EXIT: return bi_exit(argc, argv, should_exit, exit_status);
        case BUILTIN_PWD:  return bi_pwd(argc, argv);
        case BUILTIN_CD:   return bi_cd(argc, argv);
        // case BUILTIN_ECHO: return bi_echo(argc, argv);
        default:           return -1;
    }
}


static int bi_exit(int argc, char **argv, int *should_exit, int *exit_status){
    if(argc == 1){
        *should_exit = 1;
        return 0;
    }
    if(argc >= 2){
        *should_exit = 1;
        *exit_status = strtol(argv[1], NULL, 0);
        return 0;
    }
    return 1;
}

static int bi_pwd(int argc, char **argv){
    char *buf = getcwd(NULL, 0);
    if(buf == NULL) { printf("error pwd"); return 1; }
    printf(buf); putchar('\n');
    free(buf);
    return 0;
}

static int bi_cd(int argc, char **argv){
    if(argc == 1){

    }

}