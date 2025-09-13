#include "builtins.h"
#include <string.h>

BuiltinType builtin_match(const char *cmd){

}


static int bi_exit(int argc, char **argv, int *should_exit, int *exit_status);
static int bi_cd(int argc, char **argv);
static int bi_pwd(int argc, char **argv);
static int bi_echo(int argc, char **argv);

int builtin_run(BuiltinType which, int argc, char **argv,
                int *should_exit, int *exit_status) {
    switch (which) {
        case BUILTIN_EXIT: return bi_exit(argc, argv, should_exit, exit_status);
        case BUILTIN_CD:   return bi_cd(argc, argv);
        case BUILTIN_PWD:  return bi_pwd(argc, argv);
        case BUILTIN_ECHO: return bi_echo(argc, argv);
        default:           return -1;
    }
}