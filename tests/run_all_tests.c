#include <stdio.h>


void run_all_builtin_tests();
void run_all_parser_tests();

int main(void) {
    printf("Starting Test Suite...\n\n");

    run_all_builtin_tests();
    run_all_parser_tests();

    printf("ALL TEST MODULES CLEARED.\n");
    return 0;
}