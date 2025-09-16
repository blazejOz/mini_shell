#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "builtins.h"

void test_builtin_run_exit() {
    int should_exit = 0, exit_status = 0;
    char *argv1[] = {"exit", NULL};
    assert(builtin_run(BUILTIN_EXIT, 1, argv1, &should_exit, &exit_status) == 0);
    assert(should_exit == 1);

    should_exit = 0; exit_status = 0;
    char *argv2[] = {"exit", "42", NULL};
    assert(builtin_run(BUILTIN_EXIT, 2, argv2, &should_exit, &exit_status) == 0);
    assert(should_exit == 1);
    assert(exit_status == 42);
}

void test_builtin_run_pwd() {
    char *argv[] = {"pwd", NULL};
    assert(builtin_run(BUILTIN_PWD, 1, argv, NULL, NULL) == 0);

    char *argv2[] = {"pwd", "extra", NULL};
    assert(builtin_run(BUILTIN_PWD, 2, argv2, NULL, NULL) == 0);
}

int main(void) {
    test_builtin_run_exit();
    test_builtin_run_pwd();
    puts("OK: builtin_run tests passed");
    return 0;
}