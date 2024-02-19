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
	Gets user input from stdin and parses it by the relevant tokens
	inputs: n/a
	outputs: array of strings of the input separated by the tokens
	side effects: n/a
	written by Fady, Danyal
*/
char** ParseInput();
