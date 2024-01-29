// imports
#include <stdlib.h>
#include <unistd.h>

// constants
#define MAX_PATH_LENGTH 256

/*
	Gets the current working directory
	inputs: n/a
	outputs: the current working directory
	side effects: n/a
	written by Mohamed
*/
char* GetWorkingDirectory();

/*
	Changes the current working directory
	inputs: the new path for the working directory
	outputs: result of the operation
	side effects: n/a
	written by Mohamed, Danyal
*/
int ChangeWorkingDirectory(const char* path);

/*
	Gets the home directory
	inputs: n/a
	outputs: the home directory
	side effects: n/a
	written by Mohamed
*/
char* GetHomeDirectory();