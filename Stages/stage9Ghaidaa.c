#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ALIAS_LENGTH 100

// Structure for a node in the substitution list
struct SubstitutionNode {
    char label[MAX_ALIAS_LENGTH];
    char replacement[MAX_COMMAND_LENGTH];
    struct SubstitutionNode* next;
};

// Structure to maintain the substitution list
struct SubstitutionList {
    struct SubstitutionNode* head;
};

// Function to initialize a substitution list
void init_substitution_list(struct SubstitutionList* list) {
    list->head = NULL;
}

// Function to add a substitution to the list
void add_substitution(struct SubstitutionList* list, const char* label, const char* replacement) {
    struct SubstitutionNode* newNode = (struct SubstitutionNode*)malloc(sizeof(struct SubstitutionNode));
    if (newNode == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->label, label);
    strcpy(newNode->replacement, replacement);
    newNode->next = list->head;
    list->head = newNode;
}

// Function to check for circular references
int check_circular_reference(struct SubstitutionList* list, const char* label) {
    struct SubstitutionNode* current = list->head;
    while (current != NULL) {
        if (strcmp(current->label, label) == 0) {
            return 1; // Circular reference detected
        }
        current = current->next;
    }
    return 0; // No circular reference found
}

// Function to resolve command substitutions
char* resolve_command(const char* command, struct SubstitutionList* list, struct AliasPair* aliasPairs, int aliasLen) {
    char* resolvedCommand = strdup(command); // Copy the command to avoid modifying the original

    // Check for circular references
    if (check_circular_reference(list, resolvedCommand)) {
        fprintf(stderr, "Error: Circular reference detected for label '%s'\n", resolvedCommand);
        free(resolvedCommand);
        return NULL;
    }

    // Add the current command to the substitution list
    add_substitution(list, resolvedCommand, ""); // Placeholder for replacement

    // Iterate until the resolved command matches a built-in command, an external program, or is invalid
    while (1) {
        int index = index_of_alias(resolvedCommand, aliasPairs, aliasLen);
        if (index != -1) {
            char* aliasCommand = (aliasPairs + index)->command;
            // Concatenate parameters with the resolved alias command
            char* nextToken = strtok(aliasCommand, " ");
            char concatenatedCommand[MAX_COMMAND_LENGTH] = "";
            strcat(concatenatedCommand, nextToken);
            while ((nextToken = strtok(NULL, " ")) != NULL) {
                strcat(concatenatedCommand, " ");
                strcat(concatenatedCommand, nextToken);
            }
            strcpy(resolvedCommand, concatenatedCommand);
        } else {
            // Implement logic here to determine if the command is a built-in command or an external program
            // For demonstration, let's assume the command is always an external program
            break;
        }
    }

    // Update the replacement for the current command in the substitution list
    struct SubstitutionNode* current = list->head;
    while (current != NULL) {
        if (strcmp(current->label, resolvedCommand) == 0) {
            strcpy(current->replacement, resolvedCommand);
            break;
        }
        current = current->next;
    }

    return resolvedCommand;
}

// Function to find the index of an alias in the aliasPairs array
int index_of_alias(const char* alias, struct AliasPair* aliasPairs, int len) {
    for (int i = 0; i < len; i++) {
        if (strcmp((aliasPairs + i)->alias, alias) == 0) return i;
    }
    return -1;
}

int main() {
    // Sample alias pairs
    struct AliasPair aliasPairs[] = {
        {"ls", "ls -l"},
        {"ll", "ls -la"},
        // Add more alias pairs as needed
    };
    int aliasLen = sizeof(aliasPairs) / sizeof(aliasPairs[0]);

    // Initialize substitution list
    struct SubstitutionList substitutionList;
    init_substitution_list(&substitutionList);

    // Read user input
    char command[MAX_COMMAND_LENGTH];
    printf("Enter command: ");
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = '\0'; // Remove newline character from input

    // Resolve command substitutions
    char* resolvedCommand = resolve_command(command, &substitutionList, aliasPairs, aliasLen);
    if (resolvedCommand != NULL) {
        printf("Resolved Command: %s\n", resolvedCommand);
        free(resolvedCommand);
    }

    // Free memory allocated for the substitution list
    struct SubstitutionNode* current = substitutionList.head;
    while (current != NULL) {
        struct SubstitutionNode* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
