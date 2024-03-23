#include "file_handling.h"

int set_file(const char* fileLocation, char* data[], const int len)
{
    // getting the file
    FILE* fptr = fopen(fileLocation, "w");
    if (fptr == NULL)
        return -1;
    
    // writing to the file
    for (int i = 0; i < len; i++)
    {
        fprintf(fptr, "%s\n", data[i]);
    }
    
    // closing the file
    fclose(fptr);
    return 0;
}

int get_file(const char* fileLocation, char* result[], int maxLines)
{
    // getting the file
    FILE* fptr = fopen(fileLocation, "r");
    if (fptr == NULL) return -1;

    // reading from the file and writing its content to results
    char currLine[MAX_LINE_LENGTH];
    int len = 0;
    while (len < maxLines && fgets(currLine, MAX_LINE_LENGTH, fptr) != NULL)
    {
        int index = strcspn(currLine, "\n");
        if (currLine[index] == '\n')
            currLine[index] = '\0';
        strcpy(result[len], currLine);
        len++;
    }

    // closing the file
    fclose(fptr);
    return len;
}