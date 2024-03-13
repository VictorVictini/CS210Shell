// imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constants
#define MAX_BUFFER_LENGTH 513
#define MAX_ARGS_QUANTITY 20
#define TOKENS " \t|><&;"

/*
	Displays the shell prompt. Should make prompt constant?
	inputs: n/a
	outputs: n/a
	side effects: prints prompt to stdout
	written by Andrew, Fred and John
*/
void display_prompt();

/*
	Retrieves input from stdin
	inputs: the string to be edited, its max length
	outputs: 0 if it went well, otherwise -1
	side effects: any functionality reliant on the string may change
	written by Mohamed, Danyal
*/
int retrieve_input(char* str, int maxLen);

/*
	Parses provided input into tokens
	inputs: string to be split by the tokens, the args as an array of strings/equivalent, the maximum number of args
	outputs: the length of the arguments
	side effects: any functionality reliant on the args may change
	written by Fady, Danyal
*/
int parse_input(char* str, char** args, int maxArgs);