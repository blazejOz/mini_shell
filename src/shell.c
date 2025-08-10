#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"

void shell_loop(){
    char buffer[1024];

    while(1){
        printf("mini-shell> ");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\n");
            break;
        }

        //strips trailing \n
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n'){
            buffer[len-1] = '\0';
        }

        //check if empty/whitespace buffer
        if(is_blank(buffer)) continue;

        //exit the loop
        if(strcmp(buffer, "exit") == 0) break;

        printf("echo: %s\n", buffer);
    }
}

