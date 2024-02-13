// stage_2.h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifndef STAGE_2_H
#define STAGE_2_H

void execute_external_command(char **args);

#endif // STAGE_2_H
