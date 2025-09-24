#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "utils.h"
#include "parser.h"
#include "execargs.h"
#include "builtins.h"


static int run_external(ExecArgs *ea,int  *exit_status);

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

        char *tokens[MAX_TOKENS];
        int token_count = tokenize(buffer, tokens, MAX_TOKENS);
        if (token_count <= 0) continue;

        ExecArgs ea; execargs_init(&ea);

        for(int i = 0; i < token_count; i++){
            if(execargs_push(&ea, tokens[i]) != 0){
                printf("error execargs_push");
                execargs_free(&ea);
                continue;
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

        int should_exit = 0;
        int exit_status = 0;

        BuiltinType builtin = builtin_match(ea.argv[0]);
        if (builtin != BUILTIN_NONE) {
            int rc = builtin_run(builtin, ea.argc, ea.argv, &should_exit, &exit_status);
            if(should_exit){
                execargs_free(&ea);
                exit(exit_status);
            }

            execargs_free(&ea);
            continue;
        }else{
            int run_ext = run_external(&ea, &exit_status);
            execargs_free(&ea);
            continue;
        }

    }
    
}

int run_external(ExecArgs *ea, int  *exit_status){
    if (!ea || !ea->argv || !ea->argv[0]) return -1;

   pid_t pid = fork();

    if (pid == 0) {
        // Child
        execvp(ea->argv[0], ea->argv);
        perror("execvp");   
        _exit(1);           
    } else if (pid > 0) {
        // Parent
        int status;
        waitpid(pid, &status, 0);   
    } else {
        perror("fork");     
        return -1;
    }
    return 0;
}