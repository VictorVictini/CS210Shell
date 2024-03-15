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
char* invoke_from_history(char* command, int argsLen);

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

#endif // STAGE_5_H
