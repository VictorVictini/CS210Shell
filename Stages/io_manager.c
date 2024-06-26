#include "io_manager.h"

void display_prompt()
{
    printf("This is the greatest and best shell in the world >>>>> ");
}

int retrieve_input(char* str)
{
    // retrieving input
    if (fgets(str, MAX_BUFFER_LENGTH, stdin) == NULL)
        return -1;

    // if the string doesn't contain \n or NULL
    if (strchr(str, '\n') == NULL)
    {
        char chr = fgetc(stdin);
        while (chr != '\n' && chr != EOF)
        {
            chr = fgetc(stdin);
        }
    }

    // replace last character with \0, (find how many characters there are before the \n)
    str[strcspn(str, "\n")] = '\0';
    return 0;
}

int parse_input(char* str, char* args[])
{
    char* currArg = strtok(str, TOKENS);
    int len = 0;
    while (len < MAX_ARGS_QUANTITY && currArg != NULL)
    {
        args[len] = currArg;
        currArg = strtok(NULL, TOKENS);
        len++;
    }
    return len;
}