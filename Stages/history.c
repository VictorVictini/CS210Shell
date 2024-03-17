#include "history.h"

// Global variables
HistoryEntry history[HISTORY_SIZE];
int history_count = 0; // Number of commands saved in history

// Function to add a command to history
void add_to_history(char* command) {
    // If the history array is full, shift elements
    if (history_count == HISTORY_SIZE) {
        for (int i = 0; i < HISTORY_SIZE - 1; i++) {
            history[i] = history[i + 1];
            history[i].number = i + 1; // Reset the number after shifting
        }
    } else {
        history_count++; // Increment only if there is space in the array
    }

    // Create a new history entry
    HistoryEntry entry;
    entry.number = history_count;
    strncpy(entry.command, command, sizeof(entry.command) - 1);
    entry.command[sizeof(entry.command) - 1] = '\0';

    // Add the new entry to the history
    history[history_count - 1] = entry;
}

// Function to print the history
void print_history() {
    for (int i = 0; i < history_count; i++) {
        printf("%d %s\n", history[i].number, history[i].command);
    }
}

// Function to invoke a command from history
int invoke_from_history(char* input, char* command, int argsLen, char** result) {
    // Check if it is a valid history invocation
    if (strcmp(command, "!!") == 0) {
        if (argsLen != 1) {
            printf("history invocation should have no arguments.\n");
            return -1;
        }
        // Execute the latest command entered in history
        if (history_count > 0) {
            *result = strdup(history[history_count - 1].command);
            return 0;
        } else {
            printf("Error: History is empty.\n");
            return -1;
        }
    } else if (command[0] == '!' && isdigit(command[1])) {
        if (argsLen != 1) {
            printf("history invocation should have no arguments.\n");
            return -1;
        }
        // Extract the command number from the input
        int history_number = atoi(command + 1);

        // Check if the specified history number is valid
        if (history_number >= 1 && history_number <= history_count) {
            *result = strdup(history[history_number - 1].command);
            return 0;
        } else {
            printf("Error: Invalid history number.\n");
            return -1;
        }
    } else if (strncmp(command, "!-", 2) == 0 && isdigit(command[2])) {
        if (argsLen != 1) {
            printf("history invocation should have no arguments.\n");
            return -1;
        }
        // Extract the number from the input
        int offset = atoi(command + 2);

        // Calculate the history number to invoke
        int target_number = history_count - offset;

        // Check if the calculated history number is valid
        if (offset >= 1 && target_number >= 0 && target_number <= history_count) {
            *result = strdup(history[target_number].command);
            return 0;
        } else {
            printf("Error: Invalid history number.\n");
            return -1;
        }
    } else {
        // Add the entered command to history
        add_to_history(input);
        return 1;
    }
}



int save_history(char* directory)
{
    // turning into string array
    char** historyStrings = (char**)malloc(HISTORY_SIZE * sizeof(char*));
    for (int i = 0; i < history_count; i++)
    {
        historyStrings[i] = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
        sprintf(historyStrings[i], "%d %s", history[i].number, history[i].command);
    }

    // saving file
    char fileLoc[2048];
    sprintf(fileLoc, "%s/%s", directory, HIST_FILE_NAME);
    int res = set_file(fileLoc, historyStrings, history_count);

    // freeing
    for (int i = 0; i < history_count; i++) free(historyStrings[i]);
    free(historyStrings);

    return res;
}

int load_history(char* directory) {
    // reset history count to 0 to prevent glitches in memory array
    history_count = 0;

    // concat file name to directory
    char fileLoc[2048];
    sprintf(fileLoc, "%s/%s", directory, HIST_FILE_NAME);

    // turning into string array
    char** historyStrings = (char**)calloc(HISTORY_SIZE, sizeof(char*));
    for (int i = 0; i < HISTORY_SIZE; i++) {
        historyStrings[i] = (char*)calloc(MAX_LINE_LENGTH, sizeof(char));
    }
    int res = get_file(fileLoc, historyStrings, HISTORY_SIZE);

    // loading it into the history array
    for (int i = 0; i < HISTORY_SIZE; i++) {
        if (strlen(historyStrings[i]) == 0) continue;
        sscanf(historyStrings[i], "%d %[^\n]", &history[i].number, history[i].command);
        history_count++;
    }

    // freeing
    for (int i = 0; i < HISTORY_SIZE; i++) free(historyStrings[i]);
    free(historyStrings);

    return res;
}

int clear_history(char* directory) {
    // reset history count
    history_count = 0;

    // clear history array
    for (int i = 0; i < HISTORY_SIZE; i++) {
        history[i].number = 0;
        memset(history[i].command, 0, MAX_LINE_LENGTH);
    }

    // wipe history file
    char fileLoc[2048];
    sprintf(fileLoc, "%s/%s", directory, HIST_FILE_NAME);
    return set_file(fileLoc, NULL, 0);
}