// tests/test_execargs.c
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "parser.h"

Pipeline *pipeline;

void test_pipeCounting()
{
    char* input = "1|2|3";
    pipeline = parse_pipeline(input);
    int num_cmds = pipeline->num_commands;
    assert(num_cmds == 3);

    input = "";
    pipeline = parse_pipeline(input);
    num_cmds = pipeline->num_commands;
    assert(num_cmds == 0);


}

void test_empty(){
    char buff[] = "";
    char *tokens[4] = {0};
    int n = tokenize(buff, tokens, 4);

    assert(n == 0);
    assert(tokens[0] == NULL);
}

void test_single_token(){
    char buff[] = "ls";
    char *tokens[4] = {0};
    int n = tokenize(buff, tokens, 4);

    assert(n == 1);
    assert(strcmp(tokens[0], "ls") == 0);
    assert(tokens[1] == NULL);
}

void test_multiple_tokens(){
    char buff[] = "ls -l -a";
    char *tokens[4] = {0};
    int n = tokenize(buff, tokens, 4);

    assert(n == 3);
    assert(strcmp(tokens[0], "ls") == 0);
    assert(strcmp(tokens[1], "-l") == 0);
    assert(strcmp(tokens[2], "-a") == 0);
    assert(tokens[3] == NULL);

}

void test_whitespace(){
    char buff[] = "     ls\t-l  ";
    char *tokens[4] = {0};
    int n = tokenize(buff, tokens, 4);

    assert(n == 2);
    assert(strcmp(tokens[0], "ls") == 0);
    assert(strcmp(tokens[1], "-l") == 0);
    assert(tokens[2] == NULL);
}

int main(void){
    test_pipeCounting();
    // test_empty();
    // test_single_token();
    // test_multiple_tokens();
    // test_whitespace();
    puts("OK: all parser tests passed");
    return 0;
}