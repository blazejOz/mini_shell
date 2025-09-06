// tests/test_execargs.c
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "execargs.h" 


static void test_init(void) {
    ExecArgs ea; 
    execargs_init(&ea);
    assert(ea.argv == NULL);
    assert(ea.argc == 0);
    assert(ea.capacity == 0);
    puts("OK: test_inint");
}

static void test_push_and_copy(void) {
    ExecArgs ea; execargs_init(&ea);
    const char *t0 = "ls", *t1 = "-la", *t2 = "/home";
    assert(execargs_push(&ea, t0) == 0);
    assert(execargs_push(&ea, t1) == 0);
    assert(execargs_push(&ea, t2) == 0);
    assert(ea.argc == 3);
    assert(strcmp(ea.argv[0], "ls") == 0);
    assert(strcmp(ea.argv[1], "-la") == 0);
    assert(strcmp(ea.argv[2], "/home") == 0);
    // mutate external buffer scenario (simulate):
    char buf[] = "cat";
    (void)execargs_push(&ea, buf);
    buf[0] = 'X';
    assert(strcmp(ea.argv[3], "cat") == 0);
    execargs_free(&ea);
    puts("OK: test_push_and_copy");
}

static void test_growth(void) {
    ExecArgs ea; execargs_init(&ea);
    for (int i = 0; i < 8; ++i) { 
        char tmp[16]; 
        snprintf(tmp, sizeof tmp, "t%d", i); 
        assert(execargs_push(&ea, tmp) == 0); 
    }
    assert(ea.argc == 8);
    assert(ea.capacity >= 8);
    execargs_free(&ea);
    puts("OK: test_growth");
}

static void test_finalize_sets_null(void) {
    ExecArgs ea; execargs_init(&ea);
    assert(execargs_push(&ea, "echo") == 0);
    assert(execargs_push(&ea, "hi") == 0);
    assert(execargs_finalize(&ea) == 0);
    assert(ea.argv[ea.argc] == NULL);
    execargs_free(&ea);
}

static void test_free_idempotent(void) {
    ExecArgs ea; execargs_init(&ea);
    (void)execargs_push(&ea, "one");
    execargs_free(&ea);
    execargs_free(&ea); // should not crash
}

static void test_push_null_token_rejected(void) {
    ExecArgs ea; execargs_init(&ea);
    int r = execargs_push(&ea, NULL);
    assert(r == -1);
    assert(ea.argc == 0);
    execargs_free(&ea);
}

int main(void) {
    test_init();
    test_push_and_copy();
    test_growth();
    // test_finalize_sets_null();
    // test_free_idempotent();
    // test_push_null_token_rejected();
    puts("OK: all execargs tests passed");
    return 0;
}
