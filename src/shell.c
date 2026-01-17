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
    int num_cmd = pipeline->num_commands;

    if(num_cmd == 1){
        BuiltinType builtin = builtin_match(pipeline->commands[0].args[0]);
        if(builtin != BUILTIN_NONE){
            builtin_run(builtin, pipeline->commands[0].args, should_exit, exit_status);
        }
    }

    
}

