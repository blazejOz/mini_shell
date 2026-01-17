#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "utils.h"
#include "parser.h"
#include "builtins.h"


void shell_loop()
{
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


        Pipeline *pipeline = parse_pipeline(buffer);
        int should_exit = 0;
        int exit_status = 0;
        if (pipeline) {
            run_commands(pipeline, &should_exit, &exit_status);
            free_pipeline(pipeline); 
        }

        if(should_exit){ exit(exit_status); }

    }
}
    


void run_commands(Pipeline *pipeline,int* should_exit, int* exit_status){
    int num_cmds = pipeline->num_commands;

    // Run Builtin first in case its cd
    if(num_cmds == 1){
        BuiltinType builtinType = builtin_match(pipeline->commands[0].args[0]);
        if(builtinType != BUILTIN_NONE){
           *exit_status =  builtin_run(builtinType, pipeline->commands[0].args, should_exit, exit_status);
            return;
        }
    }

    // run command pipe line

    int pipe_fds[2];
    int in_fd = 0; // Start with STDIN

    for (int i = 0; i < num_cmds; i++) {
        // Create a pipe if we aren't at the last command
        if (i < num_cmds - 1) {
            if (pipe(pipe_fds) < 0) {
                perror("pipe");
                return;
            }
        }

        pid_t pid = fork();
        if (pid == 0) { 
            // CHILD
            // Redirect Input (unless it's the first command)
            if (i > 0) {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }

            // Redirect Output (unless it's the last command)
            if (i < num_cmds - 1) {
                close(pipe_fds[0]); 
                dup2(pipe_fds[1], STDOUT_FILENO);
                close(pipe_fds[1]);
            }

            // 4. Handle Builtins vs External
            BuiltinType b_type = builtin_match(pipeline->commands[i].args[0]);
            if (b_type != BUILTIN_NONE) {
                // We are in a child, so we don't care about should_exit here
                int dummy_exit = 0;
                int status = builtin_run(b_type, pipeline->commands[i].args, &dummy_exit, exit_status);
                exit(status);
            } else {
                execvp(pipeline->commands[i].args[0], pipeline->commands[i].args);
                perror("execvp"); // Only runs if execvp fails
                exit(EXIT_FAILURE);
            }
        }

        // PARENT CLEANUP
        if (i > 0) close(in_fd); // Close the "old" read end
        if (i < num_cmds - 1) {
            close(pipe_fds[1]); // Close the write end 
            in_fd = pipe_fds[0]; // Keep the read end for the NEXT command
        }
    }

    // 5. Wait for children
    int status;
    for (int i = 0; i < num_cmds; i++) {
        wait(&status);
        if (i == num_cmds - 1) { // Exit status of the pipeline is the last command
            if (WIFEXITED(status)) *exit_status = WEXITSTATUS(status);
        }
    }
    
}

