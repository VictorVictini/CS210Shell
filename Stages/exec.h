#ifndef EXEC
#define EXEC

// imports
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
    Executes an external command
    inputs: the arguments to execute
    outputs: -1 if something went wrong, otherwise 0
    side effects: n/a
    written by Nathan
*/
int execute_external_command(char* args[]);

#endif