#include "parser.h"
#include <ctype.h>
#include <stddef.h>

int tokenize(char *line, char **tokens, int max_tokens){
    char *char_ptr = line;
    int argc = 0;

    while(*char_ptr != '\0' && argc < max_tokens - 1){
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
    return argc;
}
