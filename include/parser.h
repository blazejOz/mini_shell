#ifndef PARSER_H
#define PARSER_H

#define MAX_TOKENS 64

typedef struct{
    char** args;
} Command;

typedef struct{
    Command* commands;
    int num_commands;
}Pipeline;


Pipeline* parse_pipeline(char *input);
void free_pipeline(Pipeline *pipeline);
char** tokenize(char *line);

#endif