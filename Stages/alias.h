// imports
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

// constants
#define MAX_ALIASES 10

// structs
struct AliasPair {
    char* alias;
    char* command;
};

/*
    Adds the given alias to the array with its relevant command
	inputs: the alias to be added, the related command to be added, the current pairs of commands and alias, how many pairs exist
	outputs: returns -1 if something went wrong, otherwise it returns the new length
	side effects: will change functionality of any arguments reliant on aliasPairs should the function succeed, assumes alias and command are not NULL and may result in errors otherwise
	written by Danyal
*/
int add_alias(char* alias, char* command, struct AliasPair* aliasPairs, int len);

/*
    finds the index of a given alias
	inputs: the alias to be found, all the current alias pairs, how many pairs exist
	outputs: returns the index if it was found, otherwise -1
	side effects: assumes alias is not null and may result in errors otherwise
	written by Danyal
*/
int index_of_alias(char* alias, struct AliasPair* aliasPairs, int len);

/*
    Remove the given alias from the array of pairs
	inputs: the alias to be removed, and the current aliases so it can be changed, how many pairs exist
	outputs: returns the new length, or -1 if something went wrong
	side effects: will change functionality reliant on aliases should the function succeed, assumes alias is not null and may result in errors otherwise
	written by Danyal
*/
int remove_alias(char* alias, struct AliasPair* aliasPairs, int len);

/*
    prints the details in the alias pairs
    inputs: the alias pairs to print the details of, how many pairs exist
    outputs: n/a
    side effects: n/a
    written by Danyal
*/
void print_alias(struct AliasPair* aliasPairs, int len);