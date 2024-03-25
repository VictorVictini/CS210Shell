#include "exec.h"

int execute_external_command(char* args[])
{
    pid_t pid = fork();
    if (pid == -1)
        return -1;

    if (pid == 0) // Child process
    {
        execvp(args[0], args);
        perror(args[0]);
        exit(EXIT_FAILURE);
    }
    else // Parent process
    {
        wait(NULL);
    }
    return 0;
}