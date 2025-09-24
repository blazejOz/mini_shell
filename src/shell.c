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
        // Show prompt
        printf("mini-shell> ");

        // Read one line of input from user
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\n");
            break;
        }

        //strips trailing '\n'
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n'){
            buffer[len-1] = '\0';
        }

        // Skip if input is blank
        if(is_blank(buffer)) continue;

        // Split input into tokens (words separated by spaces)
        char *tokens[MAX_TOKENS];
        int token_count = tokenize(buffer, tokens, MAX_TOKENS);
        if (token_count <= 0) continue;

        // Build ExecArgs structure from tokens
        ExecArgs ea; execargs_init(&ea);
        int push_failed = 0;
        for (int i = 0; i < token_count; i++) {
            if (execargs_push(&ea, tokens[i]) != 0) {
                fprintf(stderr, "mini-shell: execargs_push failed\n");
                push_failed = 1;
                break;             
            }
        }
        if (push_failed) { execargs_free(&ea); continue; }
        // Finalize ExecArgs (add NULL at end)
        if(execargs_finalize(&ea) != 0){
            printf("error finalize\n");
            execargs_free(&ea);
            continue;
        }

        if(ea.argc == 0){
            execargs_free(&ea);
            continue;
        }

        int should_exit = 0;
        int exit_status = 0;

        // Check if first word matches a builtin command
        BuiltinType builtin = builtin_match(ea.argv[0]);
        if (builtin != BUILTIN_NONE) {
            //run builtins
            int rc = builtin_run(builtin, ea.argc, ea.argv, &should_exit, &exit_status);
            if(should_exit){
                execargs_free(&ea);
                exit(exit_status);
            }

            execargs_free(&ea);
            continue;
        }else{
            // run external programs
            int run_ext = run_external(&ea, &exit_status);
            execargs_free(&ea);
            continue;
        }

    }
    
}

// Run an external program (not a builtin)
// ea->argv must be NULL-terminated
// Returns 0 on success, -1 on error
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
        if(exit_status) *exit_status = 0;
        return 0;  
    } else {
        // fork() failed
        perror("fork");     
        return -1;
    }
}