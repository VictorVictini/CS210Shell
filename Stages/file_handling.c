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
        // ignore all remaining chars on this line since we reached the 'MAX_LINE_LENGTH'
        if (strlen(currLine) == MAX_LINE_LENGTH - 1 && currLine[MAX_LINE_LENGTH - 2] != '\n')
        {
            char chr = fgetc(fptr);
            while (chr != '\n' && chr != EOF)
            {
                chr = fgetc(fptr);
            }
        }

        // replaces a new line if needed
        int index = strcspn(currLine, "\n");
        if (currLine[index] == '\n')
            currLine[index] = '\0';

        // adds to the array and increments length 
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
        // ignore all remaining chars on this line since we reached the 'MAX_LINE_LENGTH'
        if (strlen(buffer) == MAX_LINE_LENGTH - 1 && buffer[MAX_LINE_LENGTH - 2] != '\n')
        {
            char chr = fgetc(fptr);
            while (chr != '\n' && chr != EOF)
            {
                chr = fgetc(fptr);
            }
        }

        // increment counter
        count++;
    }
    
    return count;
}