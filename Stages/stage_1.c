#include <stdio.h>
#include "stage_1.h"

void display_prompt(){
	printf("This is the greatest and best shell in the world >>>>> ");
}

void retrieve_input(char* str, int maxLen) {
	// retrieving input
    if (fgets(str, maxLen, stdin) == NULL) return;

	// if the string doesn't contain \n or NULL
    if (strchr(str, '\n') == NULL) {
		char chr = fgetc(stdin);
        while (chr != '\n' && chr != EOF)
		{
			chr = fgetc(stdin);
		};
	}

	// replace last character with \0, (find how many characters there are before the \n)
    str[strcspn(str, "\n")] = '\0';
}

int parse_input(char* str, char** args, int maxArgs) {
	char* currArg = strtok(str, TOKENS);
	int len = 0;
	while (len < maxArgs && currArg != NULL) {
		*(args + len) = currArg;
		len++;
		currArg = strtok(NULL, TOKENS);
	}
	return len;
}
