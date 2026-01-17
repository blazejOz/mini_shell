#include "parser.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>

Pipeline* parse_pipeline(char *input)
{
    Pipeline *pipeline = malloc(sizeof(Pipeline));
    
    //Count commands divided by '|' operator
    int num_cmds = 0;
    if(!is_blank(input)) num_cmds++;
    for(int i = 0; input[i]; i++) {if (input[i] == '|') num_cmds++;}
    pipeline->num_commands = num_cmds;

    //Allocate space for the Command structs
    pipeline->commands = malloc(sizeof(Command) * num_cmds);
    
    char* cmd_str = strtok(input, "|");
    int cmd_indx = 0;

    //Parse command string into tokens and assign to command array in Pipeline
    while(cmd_str != NULL && cmd_indx < num_cmds){
        pipeline->commands[cmd_indx].args = tokenize(cmd_str);
        cmd_indx++;
        cmd_str = strtok(NULL, "|");
    }

    return pipeline;
}

char** tokenize(char *line)
{
    char *char_ptr = line;
    int argc = 0;

    char** tokens = malloc(sizeof(char) * MAX_TOKENS);

    while(*char_ptr != '\0' && argc < MAX_TOKENS - 1){
        //skip whitespace
        while(isspace((unsigned char)*char_ptr)) char_ptr++;
        
        if (*char_ptr == '\0') break;

        char *token_start = char_ptr;
        while(*char_ptr != '\0' && !isspace((unsigned char)*char_ptr))
            char_ptr++;
            
        if(*char_ptr != '\0'){
            *char_ptr = '\0';
            char_ptr++;
        }
        tokens[argc++] = token_start;
    }
    tokens[argc] = NULL;
    return tokens;
}

void free_pipeline(Pipeline *pipeline) {
    if (!pipeline) return;

    if (pipeline->commands) {
        for (int i = 0; i < pipeline->num_commands; i++) {
            if (pipeline->commands[i].args) {
                free(pipeline->commands[i].args);
            }
        }
        free(pipeline->commands);
    }
    free(pipeline);
}