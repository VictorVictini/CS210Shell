#ifndef STAGE_9
#define STAGE_9

// imports
#include <string.h>

// constants
#define MAX_ITERATIONS 500

/*
    Finds the given string (char*) in an array of string (char**)
    inputs: the string, the array of string, the length of the array of string
    outputs: 0 if found, otherwise -1
    side effects: n/a
    written by Danyal
*/
int contains(char* target, char** list, int len);

#endif