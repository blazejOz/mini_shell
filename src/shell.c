#include "shell.h"
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "parser.h"
#include "execargs.h"
#include "builtins.h"

void shell_loop(){
    char buffer[1024];

    while(1){
        printf("mini-shell> ");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\n");
            break;
        }

        //strips trailing '\n'
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n'){
            buffer[len-1] = '\0';
        }

        //check if empty/whitespace buffer
        if(is_blank(buffer)) continue;

        //exit the loop
        if(strcmp(buffer, "exit") == 0) break;

        char *tokens[MAX_TOKENS];
        int token_count = tokenize(buffer, tokens, MAX_TOKENS);
        if (token_count <= 0) continue;

        ExecArgs ea; execargs_init(&ea);

        for(int i = 0; i < token_count; i++){
            if(execargs_push(&ea, tokens[i]) != 0){
                printf("error execargs_push");
                execargs_free(&ea);
                ;
            }
        }
        
        if(execargs_finalize(&ea) != 0){
            printf("error finalize");
            execargs_free(&ea);
            continue;
        }

        if(ea.argc == 0){
            execargs_free(&ea);
            continue;
        }

        int i = 0;
        while(ea.argv[i] != NULL){
            printf("%s, ",ea.argv[i]);
            i++; 
        }

        execargs_free(&ea);
    }
}

