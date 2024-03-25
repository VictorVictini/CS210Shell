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
    if (fptr == NULL)
        return -1;

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

int count_file_lines(const char* fileLocation)
{
    // getting the file
    FILE* fptr = fopen(fileLocation, "r");
    if (fptr == NULL)
        return -1;
    
    // counting each line
    int count = 0;
    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, fptr) != NULL)
    {
        count++;
    }
    
    return count;
}