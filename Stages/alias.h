#ifndef ALIAS
#define ALIAS

// imports
#include "stdio.h"
#include "string.h"
#include "file_handling.h"
#include "io_manager.h" // to get the constant

// constants
#define MAX_ALIASES 10
#define ALIASES_FILE_NAME ".aliases"

// struct and type definition
typedef struct
{
    char alias[MAX_BUFFER_LENGTH];
    char command[MAX_BUFFER_LENGTH];
} AliasPair;

/*
    Adds the given alias to the array with its relevant command
    inputs: the alias to be added, the related command to be added, the current pairs of commands and alias, how many pairs exist
    outputs: returns -1 if something went wrong, otherwise it returns the new length
    side effects: will change functionality of any arguments reliant on aliasPairs should the function succeed, assumes alias and command are not NULL and may result in errors otherwise
    written by Danyal
*/
int add_alias(char* alias, char* command, AliasPair* aliasPairs, int len);

/*
    finds the index of a given alias
    inputs: the alias to be found, all the current alias pairs, how many pairs exist
    outputs: returns the index if it was found, otherwise -1
    side effects: assumes alias is not null and may result in errors otherwise
    written by Danyal
*/
int index_of_alias(char* alias, AliasPair* aliasPairs, int len);

/*
    Remove the given alias from the array of pairs
    inputs: the alias to be removed, and the current aliases so it can be changed, how many pairs exist
    outputs: returns the new length, or -1 if something went wrong
    side effects: will change functionality reliant on aliases should the function succeed, assumes alias is not null and may result in errors otherwise
    written by Danyal
*/
int remove_alias(char* alias, AliasPair* aliasPairs, int len);

/*
    prints the details in the alias pairs
    inputs: the alias pairs to print the details of, how many pairs exist
    outputs: n/a
    side effects: n/a
    written by Danyal
*/
void print_alias(AliasPair* aliasPairs, int len);

/*
    Parses a line of the input for the expected format (parse_input is not enough, hence custom parsing is necessary)
    inputs: the string to parse, the args to edit
    outputs: 0 if ran successfully, otherwise -1
    side effects: changes functionality reliant on the string or args passed, will break if args isn't allocated to accept 3 of the expected arguments
    written by Danyal
*/
int parse_alias_line(char* str, char* args[]);

/*
    Retrieves aliasPairs data from the file
    inputs: the file location to read from, the aliasPair array to adapt
    outputs: -1 if failed to read from file, -2 if failed to parse a line, -3 if failed to add to aliasPairs, otherwise the new length of the array is provided
    side effects: anything reliant on aliasPairs will likely be changed, even if the parsing should fail, any extra lines will be 'cut off'/ignored, will overwrite data held in aliasPairs
    written by Danyal
*/
int read_alias_file(const char* fileDirectory, AliasPair* aliasPairs);

/*
    adds the aliasPairs data to the given file
    inputs: the file location to write to, the aliasPairs array to add, the length of the array
    output: -1 if something went wrong, else 0
    side effects: n/a
    written by Danyal
*/
int set_alias_file(const char* fileDirectory, AliasPair* aliasPairs, int len);

#endif