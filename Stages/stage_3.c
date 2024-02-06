#include "stage_3.h" 
#include <stdio.h>
<<<<<<< Updated upstream
void set_path()
{
  printf("Hello, World!");
}
=======
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 512
#define MAX_PATH_LENGTH 1024

char original_path[MAX_PATH_LENGTH];
char home_directory[MAX_PATH_LENGTH];

void save_original_path() {
    char *path = getenv("HOME");
    if (path != NULL) {
        strcpy(original_path, path);
    } else {
        printf("Error: Unable to retrieve original PATH.\n");
        exit(1);
    }
}

void set_current_directory_to_home() {
    char *home = getenv("HOME");
    if (home != NULL) {
        strcpy(home_directory, home);
        if (chdir(home_directory) != 0) {
            perror("chdir");
            exit(1);
        }
        printf("Current directory changed to: %s\n", home_directory);
    } else {
        printf("Error: Unable to retrieve HOME directory.\n");
        exit(1);
    }
}

void getpath_command() {
    char *path = getenv("PATH");
    printf("Current PATH: %s\n", path);
}

void setpath_command(char *new_path) {
    if (new_path == NULL) {
        printf("Error: No path provided.\n");
        return;
    }
    if (setenv("PATH", new_path, 1) != 0) {
        perror("setenv");
    } else {
        printf("PATH set to: %s\n", new_path);
    }
}

void restore_original_path() {
    if (setenv("HOME", original_path, 1) != 0) {
        perror("setenv");
        exit(1);
    } else {
        printf("Restored original PATH: %s\n", original_path);
    }
}

void display_Prompt() {
    printf("Enter Prompt> ");
}

void parse_Input(char *input, char **thecommand) {
    char *token = strtok(input, " \t|><&;");
    int counter = 0;
    while (token != NULL) {
        thecommand[counter] = token;
        counter++;
        token = strtok(NULL, " \t|><&;");
    }
    thecommand[counter] = NULL;
}

/*int main() {
    save_original_path();
    set_current_directory_to_home();

    char input[MAX_INPUT_LENGTH];
    while (1) {
        display_Prompt();

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\nExiting the shell.\n");
            restore_original_path();
            break;
        }

        input[strcspn(input, "\n")] = '\0';
        char* thecommand[50];
        parse_Input(input, thecommand);

        if (strcmp(thecommand[0], "exit") == 0) {
            printf("Exiting the shell.\n");
            restore_original_path();
            break;
        } else if (strcmp(thecommand[0], "ls") == 0) {
            // Test 'ls' command behavior
            pid_t pid = fork();
            if (pid < 0) {
                printf("Error: Fork failed\n");
            } else if (pid == 0) {
                execvp(thecommand[0], thecommand);
                perror(thecommand[0]);
                exit(1);
            } else {
                wait(NULL);
            }
        } else if (strcmp(thecommand[0], "myShell") == 0) {
            // Test 'myShell' command behavior
            printf("Executing myShell command...\n");
        } else if (strcmp(thecommand[0], "getpath") == 0) {
            // Test 'getpath' command behavior
            getpath_command();
        } else if (strcmp(thecommand[0], "setpath") == 0) {
            // Test 'setpath' command behavior
            setpath_command(thecommand[1]);
        } else {
            // Execute external commands or handle other built-in commands
            pid_t pid = fork();
            if (pid < 0) {
                printf("Error: Fork failed\n");
            } else if (pid == 0) {
                execvp(thecommand[0], thecommand);
                perror(thecommand[0]);
                exit(1);
            } else {
                wait(NULL);
            }
        }
    }

    return 0;
}*/
>>>>>>> Stashed changes
