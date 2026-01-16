#ifndef PARSER_H
#define PARSER_H

#define MAX_TOKENS 64
#define MAX_COMMANDS 16

typedef struct{
    char** args;
    int argc;
} Command;

typedef struct{
    Command* commands;
    int num_commands;
}Pipeline;


Pipeline* parse_pipeline(char *input);
void free_pipeline(Pipeline *pipeline);
int tokenize(char *line, char **argv, int max_tokens);

#endif