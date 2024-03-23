#ifndef CHANGE_DIR
#define CHANGE_DIR

#include <unistd.h> 
#include <stdio.h> 

/*
    Changes the directory to the provided one
    inputs: the directory to change to
    outputs: n/a
    side effects: functionality dependant on the current working directory will be changed
    written by Lex Atkinson
*/
void change_directory(char* dir);

#endif