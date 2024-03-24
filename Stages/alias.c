#include "alias.h"

int add_alias(char* alias, char* command, AliasPair* aliasPairs, int len)
{
    // checking the current amount
    int aliasIndex = index_of_alias(alias, aliasPairs, len);
    if (len > MAX_ALIASES)
        return -1;
    if (len == MAX_ALIASES && aliasIndex == -1)
        return -1;

    // if it was found, we replace its command
    if (aliasIndex != -1)
    {
        printf("Overwriting alias \"%s\" with old command \"%s\"\n", alias, aliasPairs[aliasIndex].command);
        strcpy(aliasPairs[aliasIndex].command, command);
        return len;
    }

    // adds a new aliasPair
    strcpy(aliasPairs[len].alias, alias);
    strcpy(aliasPairs[len].command, command);
    return len + 1;
}

int remove_alias(char* alias, AliasPair* aliasPairs, int len)
{
    // if the alias does not exist in the pairs, also acts as a length check
    int index = index_of_alias(alias, aliasPairs, len);
    if (index == -1)
        return -1;

    // swap the given index with the last 'filled' index then set the last 'filled' index's values to null
    // this process is combined for efficiency
    strcpy(aliasPairs[index].alias, aliasPairs[len - 1].alias);
    strcpy(aliasPairs[index].command, aliasPairs[len - 1].command);
    aliasPairs[len - 1].command[0] = '\0';
    aliasPairs[len - 1].alias[0] = '\0';
    return len - 1;
}

int index_of_alias(char* alias, AliasPair* aliasPairs, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (strcmp(aliasPairs[i].alias, alias) == 0)
            return i;
    }
    return -1;
}

void print_alias(AliasPair* aliasPairs, int len)
{
    if (len == 0)
    {
        printf("There are currently no aliases created.\n");
        return;
    }
    for (int i = 0; i < len; i++)
    {
        printf("\"%s\" is an alias for \"%s\"\n", aliasPairs[i].alias, aliasPairs[i].command);
    }
}

int parse_alias_line(char* str, char** args)
{
    // ensuring first argument is not a token
    for (int i = 0; TOKENS[i] != '\0'; i++)
    {
        if (TOKENS[i] == str[0])
            return -1;
    }

    // finding the first instance of a token
    char* firstToken = NULL;
    for (int i = 0; TOKENS[i] != '\0' && firstToken == NULL; i++)
    {
        firstToken = strchr(str, TOKENS[i]);
    }
    if (firstToken == NULL)
        return -1;

    // finding the 2nd arg i.e. the first non-token char after the given token
    char* secArg = &firstToken[1];
    while (secArg[0] != '\0' && strchr(TOKENS, secArg[0]) != NULL)
    {
        secArg++;
    }
    if (secArg[0] == '\0')
        return -1;

    // assign memory locations to args
    args[0] = str;
    firstToken[0] = '\0';
    args[1] = secArg;

    return 0;
}

int read_alias_file(const char* fileDirectory, AliasPair* aliasPairs)
{
    // creating file location
    char fileLocation[MAX_FILE_LOCATION_LENGTH];
    sprintf(fileLocation, "%s/%s", fileDirectory, ALIASES_FILE_NAME);

    // reading from file
    char* fileData[MAX_ALIASES];
    for (int i = 0; i < MAX_ALIASES; i++)
    {
        fileData[i] = (char*)malloc(sizeof(char) * MAX_BUFFER_LENGTH);
    }
    int aliasLen = get_file(fileLocation, fileData, MAX_ALIASES);
    if (aliasLen == -1)
        return -1;

    // parsing and assigning for the relevant aliases
    char* args[2];
    for (int i = 0; i < aliasLen; i++)
    {
        if (parse_alias_line(fileData[i], args) == -1)
            return -2;
        if (add_alias(args[0], args[1], aliasPairs, i) == -1)
            return -3;
    }

    // freeing stuff
    for (int i = 0; i < MAX_ALIASES; i++)
    {
        free(fileData[i]);
    }
    return aliasLen;
}

int set_alias_file(const char* fileDirectory, AliasPair* aliasPairs, int len)
{
    // creating file location
    char fileLocation[MAX_FILE_LOCATION_LENGTH];
    sprintf(fileLocation, "%s/%s", fileDirectory, ALIASES_FILE_NAME);

    // setting fileData to be an array of string of the required format
    char* fileData[len];
    for (int i = 0; i < len; i++)
    {
        fileData[i] = (char*)calloc(sizeof(char*), MAX_BUFFER_LENGTH);
        sprintf(fileData[i], "%s %s", aliasPairs[i].alias, aliasPairs[i].command);
    }

    // letting the other function handle the file handling
    if (set_file(fileLocation, fileData, len) == -1)
        return -1;
    
    // freeing memory
    for (int i = 0; i < len; i++)
    {
        free(fileData[i]);
    }
    return 0;
}