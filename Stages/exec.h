#ifndef EXEC
#define EXEC

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_external_command(char **args);

#endif // STAGE_2_H
