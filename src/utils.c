#include <ctype.h>

// checks if string is all whitespaces
int is_blank(char *s){
    while (*s != '\0'){
        if( !isspace(*s))
            return 0;
        s++;
    }
    return 1;
}
