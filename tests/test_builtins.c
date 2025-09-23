#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "builtins.h"

void test_builtin_exit() {
    //test: exit
    int should_exit = 0, exit_status = 0;
    char *argv1[] = {"exit", NULL};
    assert(builtin_run(BUILTIN_EXIT, 1, argv1, &should_exit, &exit_status) == 0);
    assert(should_exit == 1);

    //test: exit 42
    should_exit = 0; exit_status = 0;
    char *argv2[] = {"exit", "42", NULL};
    assert(builtin_run(BUILTIN_EXIT, 2, argv2, &should_exit, &exit_status) == 0);
    assert(should_exit == 1);
    assert(exit_status == 42);

    //test: exit foo -> error, don't exit
    should_exit = 0; exit_status = 0;
    char *argv3[] = {"exit", "foo", NULL};
    assert(builtin_run(BUILTIN_EXIT, 2, argv3, &should_exit, &exit_status) != 0);
    assert(should_exit == 0);

    //test: exit 1 2 -> too many args, don't exit
    should_exit = 0; exit_status = 0;
    char *argv4[] = {"exit", "1", "2", NULL};
    assert(builtin_run(BUILTIN_EXIT, 3, argv4, &should_exit, &exit_status) != 0);
    assert(should_exit == 0);
}

void test_builtin_pwd() {
    //test: pwd
    char *argv[] = {"pwd", NULL};
    assert(builtin_run(BUILTIN_PWD, 1, argv, NULL, NULL) == 0);

    //test: too many args
    char *argv2[] = {"pwd", "extra", NULL};
    assert(builtin_run(BUILTIN_PWD, 2, argv2, NULL, NULL) != 0);
}

void test_builtin_cd(){
    char *start = getcwd(NULL, 0);
    assert(start != NULL);

    // cd with no args -> should go to HOME
    char *argv1[] = {"cd", NULL};
    assert(builtin_run(BUILTIN_CD, 1, argv1, NULL, NULL) == 0);
    char *cwd1 = getcwd(NULL, 0);
    assert(strcmp(cwd1, getenv("HOME")) == 0);
    free(cwd1);

    // cd to /tmp
    char *argv2[] = {"cd", "/tmp", NULL};
    assert(builtin_run(BUILTIN_CD, 2, argv2, NULL, NULL) == 0);
    char *cwd2 = getcwd(NULL, 0);
    assert(strcmp(cwd2, "/tmp") == 0);
    free(cwd2);

    // cd with too many args
    char *argv3[] = {"cd", "foo", "bar", NULL};
    assert(builtin_run(BUILTIN_CD, 3, argv3, NULL, NULL) != 0);

    // cd into non-existent dir
    char *argv4[] = {"cd", "/this_does_not_exist", NULL};
    assert(builtin_run(BUILTIN_CD, 2, argv4, NULL, NULL) != 0);

    // restore original dir
    chdir(start);
    free(start);

}

int main(void) {
    test_builtin_exit();
    test_builtin_pwd();
    test_builtin_cd();
    puts("OK: builtin_run tests passed");
    return 0;
}