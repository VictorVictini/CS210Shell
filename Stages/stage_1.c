#include <stdio.h>
#include "stage_1.h"

void display_prompt(){
	printf("This is the greatest and best shell in the world >>>>> ");
}

char** ParseInput() {
	// retrieving input
	char* buffer = (char*)malloc(sizeof(char*) * MAX_BUFFER_LENGTH);
    if (fgets(buffer, MAX_BUFFER_LENGTH, stdin) == NULL) return NULL;

	// if the string doesn't contain \n or NULL
    if (strchr(buffer, '\n') == NULL) {
		char chr = fgetc(stdin);
        while (chr != '\n' && chr != EOF);
	}

	// replace last character with \0, (find how many characters there are before the \n)
    buffer[strcspn(buffer, "\n")] = '\0';
	
	// return the input split by its tokens
	char** result = (char**)calloc(MAX_ARGS_QUANTITY, sizeof(char**));
	char* currArg = strtok(buffer, TOKENS);
	for (int i = 0; i < MAX_ARGS_QUANTITY && currArg != NULL; i++, currArg = strtok(NULL, TOKENS)) {
		*(result + i) = currArg;
	}

	return result;
}
