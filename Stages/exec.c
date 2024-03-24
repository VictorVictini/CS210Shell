#include "exec.h"

void execute_external_command(char* args[])
{
    pid_t pid = fork();
    if (pid == 0) // Child process
    {
        execvp(args[0], args);
        perror(args[0]);
        exit(EXIT_FAILURE);
    }
    else if (pid > 0) // Parent process
    {
        wait(NULL);
    }
    else
    {
        printf("Error: Failed to fork!\n");
    }
}