#ifndef HISTORY
#define HISTORY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "file_handling.h"

// constants
#define HIST_FILE_NAME ".hist_list"
#define HISTORY_SIZE 20

/*
    adds a command to history
    inputs: the command to add, history, the current length of history
    outputs: -1 if something went wrong, otherwise the length of history
    side effects: functionality dependant on history may change
    written by Nathan, Danyal
*/
int add_to_history(char* command, char* history[], int len);

/*
    prints history details
    inputs: history, its length
    outputs: n/a
    side effects: n/a
    written by Nathan, Danyal
*/
void print_history(char* history[], int len);

/*
    provides the command to invoke
    inputs: the input, the command to edit, history, history length
    outputs: -1 if something went wrong, otherwise 0
    side effects: functionality dependant on the command may change
    written by Nathan, Danyal
*/
int invoke_from_history(char* input, char* command, char* history[], int len);

/*
    Saves the history to a file
    inputs: the directory to find the file, the history to write to the file, history length
    outputs: -1 if something went wrong, otherwise 0
    side effects: functionality dependant on the file contents may change
    written by Mohamed, Danyal
*/
int save_history(char* directory, char* history[], int len);

/*
    Loads the history into the provided history parameter
    inputs: the directory to retrieve the file from, history to load in
    outputs: -1 if something went wrong, otherwise the history length
    side effects: functionality dependant on history may be changed
    written by Mohamed, Danyal
*/
int load_history(char* directory, char* history[]);

/*
    Determines if the given command is a history invocation
    inputs: the string
    outputs: 0 if it is a history invocation, otherwise -1
    side effects: n/a
    written by Danyal
*/
int is_history_invocation(char* command);

#endif