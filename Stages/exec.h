#ifndef EXEC
#define EXEC

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
    Executes an external command
    inputs: the arguments to execute
    outputs: n/a
    side effects: n/a
    written by Nathan
*/
void execute_external_command(char* args[]);

#endif