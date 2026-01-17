#ifndef SHELL_H
#define SHELL_H

#include "parser.h"

void shell_loop(void);
void run_commands(Pipeline *pipeline, int *should_exit, int *exit_status);

#endif