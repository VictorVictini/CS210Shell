#ifndef STAGE_5_6_H
#define STAGE_5_6_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "file_handling.h"

// constants
#define HIST_FILE_NAME ".hist_file"
#define HISTORY_SIZE 20

// Struct to represent a history entry
typedef struct {
    int number;
    char command[MAX_LINE_LENGTH];
} HistoryEntry;

// Function declarations
void add_to_history(char* command);
void print_history();
int invoke_from_history(char* input, char* command, char** result);

/*
	Saves the history
	written by Mohamed
*/
int save_history(char* directory);

/*
	Loads the history
	written by Mohamed
*/
int load_history(char* directory);

//clears history (Nathan)
int clear_history(char* directory);

/*
	Determines if the given command is a history invocation
	inputs: the string
	outputs: 0 if it is a history invocation, otherwise -1
	side effects: n/a
	written by Danyal
*/
int is_history_invocation(char* command);

#endif // STAGE_5_H