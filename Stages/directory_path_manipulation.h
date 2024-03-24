#ifndef DIRECTORY_PATH_MANIPULATION
#define DIRECTORY_PATH_MANIPULATION

// imports
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// constants
#define MAX_PATH_LENGTH 1024

/*
    Changes the current working directory
    inputs: the new path for the working directory
    outputs: result of the operation
    side effects: functionality dependant on the string provided will be changed
    written by Mohamed, Danyal
*/
int change_working_directory(const char* path);

/*
    Gets the home directory
    inputs: the string to write the home directory to
    outputs: n/a
    side effects: functionality dependant on the string will be changed
    written by Mohamed
*/
void get_home_directory(char* home);

/*
    Changes the path environment variable
    inputs: the new path for the path
    outputs: result of the operation
    side effects: n/a
    written by Ghaidaa
*/
int change_path_env(const char* path);

/*
    Gets the path environment variable
    inputs: the string to write the path to
    outputs: result of the operation
    side effects: n/a
    written by Ghaidaa
*/
void get_path_env(char* path);

/*
    Changes the directory to the provided one
    inputs: the directory to change to
    outputs: n/a
    side effects: functionality dependant on the current working directory will be changed
    written by Lex Atkinson
*/
void change_directory(char* dir);

#endif