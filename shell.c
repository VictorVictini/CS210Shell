#include "shell.h"

int main()
{
    //Find the user home directory from the environment (3)
    char homeDir[MAX_PATH_LENGTH];
    get_home_directory(homeDir);

    //Save the current path (3)
    char savedPath[MAX_PATH_LENGTH];
    get_path_env(savedPath);

    //Set current working directory to user home directory (3)
    if (change_working_directory(homeDir) == -1)
    {
        printf("Failed to change working directory.\n");
        return 1;
    }
    
    //Load history (6)
    char* history[HISTORY_SIZE];
    for (int i = 0; i < HISTORY_SIZE; i++)
    {
        history[i] = (char*)malloc(sizeof(char) * MAX_BUFFER_LENGTH);
    }
    int historyLen = load_history(homeDir, history);
    if (historyLen == -1)
    {
        printf("Could not find %s at %s when trying to load history.\n", HIST_FILE_NAME, homeDir);
        historyLen = 0; // reset count
    }
    
    //Load aliases (8)
    AliasPair aliasPairs[MAX_ALIASES];
    int aliasLen = read_alias_file(homeDir, aliasPairs);
    if (aliasLen == -1)
        printf("Failed to open the file \"%s\" at \"%s\"\n", ALIASES_FILE_NAME, homeDir);
    if (aliasLen == -2)
        printf("Failed to parse a line in the file \"%s\" at \"%s\"\n", ALIASES_FILE_NAME, homeDir);
    if (aliasLen == -3)
        printf("Failed to add to the list of aliases. There are too many aliases. The limit is %d\n", MAX_ALIASES);
    if (aliasLen < 0) // reset count
        aliasLen = 0;
    
    //Do while shell has not terminated
    while(1)
    {
        //Display prompt (1)
        display_prompt();

        //Read and parse user originInput (1)
        // reads input
        char originInput[MAX_BUFFER_LENGTH];
        if (retrieve_input(originInput) == -1)
            break;

        // creates a copy for manipulation elsewhere
        char recentInput[MAX_BUFFER_LENGTH];
        char backgroundInput[MAX_BUFFER_LENGTH];
        strcpy(backgroundInput, originInput);
        strcpy(recentInput, originInput);

        // parses input using copy
        char* args[MAX_ARGS_QUANTITY];
        int argsLen = parse_input(backgroundInput, args);

        // linked list to store all iterated commands, used to look for cycles
        LinkedList list = NULL;

        // loop until an error occurs, the max iterations occur, or it naturally ends
        int error = 0;
        while (1)
        {
            // the command has been repeated
            if (contains(args[0], list) == 0)
            {
                printf("Could not run the command as a cycle had occured.\n");
                error = -1;
                break;
            }

            if (argsLen <= 0)
                break;

            // adding it to the list so we can check if it is repeated later
            ListNode* node = (ListNode*)malloc(sizeof(ListNode*));
            strcpy(node->command, args[0]);
            add_node(node, &list);

            // making a history invocation if it is one
            if (is_history_invocation(backgroundInput) == 0)
            {
                if (argsLen != 1)
                {
                    printf("Error: history invocation should have no arguments.\n");
                    error = -1;
                    break;
                }

                if (historyLen == 0)
                {
                    printf("Error: History is empty.\n");
                    error = -1;
                    break;
                }

                // replaces the backgroundInput with the relevant command from history based on recentInput, or returns an error -1
                if (invoke_from_history(recentInput, backgroundInput, history, historyLen) == -1)
                {
                    printf("Error: invalid number provided\n");
                    error = -1;
                    break;
                }

            // replacing relevant alias if it is one
            }
            else if (argsLen > 0 && index_of_alias(args[0], aliasPairs, aliasLen) != -1)
            {
                int aliasIndex = index_of_alias(args[0], aliasPairs, aliasLen);
                if (argsLen > 1)
                {
                    // get the length of the first argument and add everything else from the input line
                    // consequently reconstructing the line to fit expectations
                    int len = 0;
                    while (args[0][len] != '\0')
                    {
                        len++;
                    }
                    sprintf(backgroundInput, "%s%s", aliasPairs[aliasIndex].command, &recentInput[len]);
                }
                else
                {
                    strcpy(backgroundInput, (aliasPairs + aliasIndex)->command);
                }
            
            // normal command/rubbish so can end this
            }
            else
            {
                break;
            }

            // parses command
            strcpy(recentInput, backgroundInput);
            argsLen = parse_input(backgroundInput, args);
        }

        // freeing list
        while (list != NULL)
        {
            ListNode* next = list->next;
            free(list);
            list = next;
        }

        // if it is an empty command, skip it
        if (argsLen <= 0)
            continue;

        // if the command is not a history invocation, add it to history
        if (is_history_invocation(originInput) != 0)
        {
            historyLen = add_to_history(originInput, history, historyLen);
        }

        // if any errors occur, end this command execution
        if (error != 0)
            continue;

        if (strcmp("exit", args[0]) == 0)
            break;

        if (strcmp("getpath", args[0]) == 0)
        {
            if (argsLen > 1)
            {
                printf("getpath should have no arguments.\n");
            }
            else
            {
                char path[MAX_PATH_LENGTH];
                get_path_env(path);
                printf("%s\n", path);
            }
        }
        else if (strcmp("setpath", args[0]) == 0)
        {
            if (argsLen < 2)
            {
                printf("No argument provided for setpath.\n");
            }
            else if (argsLen > 2)
            {
                printf("Too many arguments provided for setpath.\n");
            }
            else
            {
                char* newPath = args[1];
                change_path_env(newPath);
                printf("New path changed to %s\n", newPath);
            }
        }
        else if (strcmp("cd", args[0]) == 0)
        {
            if (argsLen == 1)
            {
                change_directory(homeDir);
            }
            else if(argsLen == 2)
            {
                change_directory(args[1]);
            }
            else
            {
                printf("Too many arguments provided for cd\n");
            }
        }
        else if (strcmp("history", args[0]) == 0)
        {
            if (argsLen == 1)
            {
                print_history(history, historyLen);
            }
            else
            {
                printf("history should have no arguments.\n");
            }
        }
        else if (strcmp("alias", args[0]) == 0)
        {
            if (argsLen == 1)
            {
                print_alias(aliasPairs, aliasLen);
            }
            else if (argsLen == 2)
            {
                printf("Alias cannot accept only one argument.\n");
            }
            else
            {
                // creates a copy for manipulation elsewhere
                char inputCopy[MAX_BUFFER_LENGTH];
                strcpy(inputCopy, recentInput);

                // parses originInput using copy
                char* aliasArgs[2];
                if (parse_alias_line(&inputCopy[6], aliasArgs) != 0)
                {
                    printf("Could not parse command. Please separate the alias and command with a space.\n");
                }
                else
                {
                    int tempLen = add_alias(aliasArgs[0], aliasArgs[1], aliasPairs, aliasLen);
                    if (tempLen == -1)
                    {
                        printf("Could not add alias \"%s\" to the list since there are too many aliases.\n", aliasArgs[0]);
                    }
                    else
                    {
                        aliasLen = tempLen;
                        printf("Successfully added alias \"%s\" with command \"%s\"\n", aliasArgs[0], aliasArgs[1]);
                    }
                }
            }
        }
        else if (strcmp("unalias", args[0]) == 0)
        {
            if (argsLen != 2)
            {
                printf("Unalias can only accept exactly one argument.\n");
            }
            else
            {
                int tempLen = remove_alias(&recentInput[8], aliasPairs, aliasLen);
                if (tempLen != -1)
                {
                    aliasLen = tempLen;
                    printf("Successfully removed alias \"%s\"\n", &recentInput[8]);
                }
                else
                {
                    printf("Could not find provided alias \"%s\".\n", &recentInput[8]);
                }
            }
        }
        else if (argsLen >= 2 && strcmp("clear", args[0]) == 0 && strcmp("history", args[1]) == 0)
        {
            if (argsLen > 2)
            {
                printf("clear history does not accept arguments.\n");
            }
            else
            {
                historyLen = 0;
                printf("Successfully cleared history\n");
            }
        }
        else 
        {
            execute_external_command(args);
        }
    }
    
    //Save history (6)
    if (save_history(homeDir, history, historyLen) == -1)
        printf("Could not write to %s at %s when trying to save history.\n", HIST_FILE_NAME, homeDir);

    // freeing history
    for (int i = 0; i < HISTORY_SIZE; i++)
    {
        free(history[i]);
    }
    
    //Save aliases (8)
    if (set_alias_file(homeDir, aliasPairs, aliasLen) == -1)
        printf("Failed to add aliases to the file \"%s\" at \"%s\"\n", ALIASES_FILE_NAME, homeDir);
    
    //Restore original path (3)
    change_path_env(savedPath);

    char restoredPath[MAX_PATH_LENGTH];
    get_path_env(restoredPath);
    printf("Path restored: %s\n", restoredPath);
    
    return 0;
}