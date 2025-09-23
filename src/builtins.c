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
    if (strcmp(cmd, "echo") == 0) return BUILTIN_ECHO; 
    return BUILTIN_NONE;
}

static int bi_exit(int argc, char **argv, int *should_exit, int *exit_status);
static int bi_pwd(int argc, char **argv);
static int bi_cd(int argc, char **argv);
static int bi_echo(int argc, char **argv);

int builtin_run(BuiltinType which, int argc, char **argv,
                int *should_exit, int *exit_status) {
    switch (which) {
        case BUILTIN_EXIT: return bi_exit(argc, argv, should_exit, exit_status);
        case BUILTIN_PWD:  return bi_pwd(argc, argv);
        case BUILTIN_CD:   return bi_cd(argc, argv);
        case BUILTIN_ECHO: return bi_echo(argc, argv);
        default:           return -1;
    }
}

/*
Builtin: exit
Usage:
  exit        -> exit shell with status 0
  exit N      -> exit shell with status N (only low 8 bits matter in shells)
  exit N M... -> error: too many arguments, do not exit
  exit foo    -> error: not a valid number, do not exit 
*/
static int bi_exit(int argc, char **argv, int *should_exit, int *exit_status){
    // Case: "exit" with extra arguments beyond one -> error, don't exit
    if(argc > 2){
        fprintf(stderr, "exit: too many arguments\n");
        return 1;
    }

    // Case: plain "exit" with no arguments -> exit with status 0
    if(argc == 1){
        *exit_status = 0;
        *should_exit = 1;   // tell the shell loop to break
        return 0;
    }

    // Case: "exit N"
    if(argc == 2){
        char *end = NULL;
        long num = strtol(argv[1], &end, 10);

        // Check if the whole string was a valid number
        if(end == argv[1] || *end != '\0') {
            // Nothing parsed or junk after digits -> not numeric
            fprintf(stderr, "exit: %s: numeric argument required\n", argv[1]);
            return 1;   // nonzero return, but shell keeps running
        }

        // Valid number -> exit with given status
        *exit_status = (unsigned char)num; // keep only low 8 bits
        *should_exit = 1;
        return 0;
    }

    // Fallback (should never happen)
    return 1;
}
/*
Builtin: pwd
Usage:
  pwd        -> print the current working directory
  pwd ARGS.. -> error: too many arguments
*/
  static int bi_pwd(int argc, char **argv){
    if (argc > 1) {
    fprintf(stderr, "pwd: too many arguments\n");
    return 1;
    }

    char *buf = getcwd(NULL, 0);
    if(buf == NULL) { 
        perror("pwd"); 
        return 1; 
    }
    printf("%s\n", buf);
    free(buf);
    return 0;
}

static int bi_cd(int argc, char **argv){
    if(argc == 1){
        char *home = getenv("HOME");
        if(home == NULL){
            fprintf(stderr, "cd: HOME env variable error\n");
            return 1;
        }
        if(chdir(home) != 0){
            perror("cd");
            return 1;
        }
        return 0;
    }
    if(argc > 2){
        fprintf(stderr, "cd: too many arguments\n");
        return 1;
    }

    char *target = argv[1];
    if(chdir(target) != 0){
        perror("cd");
        return 1;
    }
    return 0;
}

static int bi_echo(int argc, char **argv){
    for(int i = 1; i < argc; ++i) {
        printf("%s", argv[i]);
        if(i < argc - 1)
            putchar(' ');
    }
    putchar('\n');
    return 0;
}