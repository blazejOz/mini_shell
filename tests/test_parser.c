// tests/test_execargs.c
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "parser.h"



void test_pipeCounting() 
{
    char input1[] = "1|2|3";
    Pipeline *p1 = parse_pipeline(input1);
    assert(p1->num_commands == 3);
    free_pipeline(p1);

    char input2[] = "";
    Pipeline *p2 = parse_pipeline(input2);
    assert(p2->num_commands == 0);
    free_pipeline(p2);
    
    printf("test_pipeCounting passed\n");
}

void test_empty() 
{
    char input[] = "";
    Pipeline *p = parse_pipeline(input);

   
    if (p == NULL) {
        assert(p == NULL);
    } else {
        assert(p->num_commands == 0);
        free_pipeline(p); 
    }
    printf("test_empty passed\n");
}

void test_single_command() 
{
    char input[] = "ls -la";
    Pipeline *p = parse_pipeline(input);

    assert(p != NULL);
    assert(p->num_commands == 1);

    assert(strcmp(p->commands[0].args[0], "ls") == 0);
    assert(strcmp(p->commands[0].args[1], "-la") == 0);
    assert(p->commands[0].args[2] == NULL); 

    free_pipeline(p);
    printf("test_single_command passed\n");
}


int main(void){
    test_pipeCounting();
    test_empty();
    test_single_command();

    puts("OK: all parser tests passed");
    return 0;
}