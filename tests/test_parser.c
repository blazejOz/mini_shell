// tests/test_execargs.c
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "parser.h"



void test_empty(){
    char buff[] = "";
    char *tokens[4] = {0};
    int n = tokenize(buff, tokens, 4);

    assert(n == 0);
    assert(tokens[0] == NULL);
}

int main(void){
    test_empty();

    puts("OK: test_parser");
    return 0;
}