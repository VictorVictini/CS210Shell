#ifndef FILE_HANDLING
#define FILE_HANDLING

// imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constants
#define MAX_LINE_LENGTH 513

/*
    Assigns/re-assigns values to a given file
    inputs: file location, data to be inputted into file as char** (array of strings), the length of the array of strings (assumed to be correct)
    outputs: returns -1 if something went wrong, otherwise 0
    side effects: may change other functionality reliant on the file's data, will cause a segfault if the length of the array of strings is wrong
    written by Danyal
*/
int set_file(const char* fileLocation, char** data, const int len);

/*
    Retrieves data from file and places into 'result' parameter
    inputs: file location, result parameter where data is stored, maximum number of lines to check the file for
    outputs: returns -1 if something went wrong, otherwise the number of lines successfully parsed
    side effects: will create segfault error if memory is not allocated correctly for result parameter
    written by Danyal
*/
int get_file(const char* fileLocation, char** result, int maxLines);

#endif