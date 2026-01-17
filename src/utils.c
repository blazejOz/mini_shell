#include <ctype.h>
#include <stdlib.h>
#include <string.h> 

// checks if string is all whitespaces
int is_blank(char *s)
{
    while (*s != '\0'){
        if( !isspace(*s))
            return 0;
        s++;
    }
    return 1;
}

char *c_string_duplication(const char *s)
{
    if(s==NULL) return NULL;

    size_t len = strlen(s) + 1;
    char *copy = malloc(len);
    if (copy == NULL) return NULL;

    memcpy(copy, s, len);
    return copy;
}


int count_args(char** args)
{
    int argc = 0;
    
    while(args[argc] != NULL){ argc++; }

    return argc;
}


