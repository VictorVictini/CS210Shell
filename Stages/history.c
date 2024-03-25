#include "history.h"

int add_to_history(char* command, char* history[], int len)
{
    // if the history array is full, shift elements then add it
    if (len == HISTORY_SIZE)
    {
        for (int i = 1; i < len; i++)
        {
            strcpy(history[i - 1], history[i]);
        }
        strcpy(history[len - 1], command);
        return len;
    }

    // add normally
    strcpy(history[len], command);
    return len + 1;
}

// Function to print the history
void print_history(char* history[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d %s\n", i + 1, history[i]);
    }
}

// Function to invoke a command from history
int invoke_from_history(char* input, char* command, char* history[], int len)
{
    // finds the index with respect to the command
    int index = -1; // 1-indexed
    if (input[1] == '!') // !! gets the last history command
    {
        if (input[2] != '\0')
            return -2;
        index = len;
    }
    else // parse the number
    {
        // validates the format of !N or !-N where N is a positive whole number
        int chrIndex = 1;
        if (input[chrIndex] == '-')
            chrIndex++;
        while (input[chrIndex] != '\0')
        {
            if (input[chrIndex] < '0' || input[chrIndex] > '9')
                return -2;
            chrIndex++;
        }

        // parses it with further format/issue checks
        int format = sscanf(input, "!%d", &index);
        if (format == EOF || format != 1)
            return -2;

        if (index < 0) // if it is negative, assume it is !-N so add the length to get a normal history execution
            index += len + 1;
    }

    // out of range errors
    if (index < 1 || index > len)
        return -1;

    // add the relevant command from history to the provided string
    strcpy(command, history[index - 1]);
    return 0;
}

int save_history(char* directory, char* history[], int len)
{
    // concat file name to directory
    char fileLoc[MAX_FILE_LOCATION_LENGTH];
    sprintf(fileLoc, "%s/%s", directory, HIST_FILE_NAME);

    // saves history to file
    return set_file(fileLoc, history, len);
}

int load_history(char* directory, char* history[])
{
    // concat file name to directory
    char fileLoc[MAX_FILE_LOCATION_LENGTH];
    sprintf(fileLoc, "%s/%s", directory, HIST_FILE_NAME);

    // loads into buffer from file
    char* buffer[HISTORY_SIZE + 1];
    for (int i = 0; i <= HISTORY_SIZE; i++)
    {
        buffer[i] = (char*)malloc(sizeof(char) * MAX_BUFFER_LENGTH);
    }
    int len = get_file(fileLoc, buffer, HISTORY_SIZE + 1);
    
    // if there are too many lines
    if (len > HISTORY_SIZE)
        return -2;

    // if the file failed to load
    if (len == -1)
        return -1;

    // writes buffer to history
    for (int i = 0; i < len; i++)
    {
        strcpy(history[i], buffer[i]);
    }

    // free()-ing buffer
    for (int i = 0; i <= HISTORY_SIZE; i++)
    {
        free(buffer[i]);
    }

    return len;
}

int is_history_invocation(char* command)
{
    if (*command == '!')
        return 0;
    return -1;
}