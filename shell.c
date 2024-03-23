#include "shell.h"

int main()
{
	//Find the user home directory from the environment (3)
	char* home_dir = GetHomeDirectory();

	//Save the current path (3)
	char* saved_path = GetPathEnv();

	//Set current working directory to user home directory (3)
	if (ChangeWorkingDirectory(home_dir) == -1)
	{
		printf("Failed to change working directory.\n");
		return 1;
	}
	
	//Load history (6)
	if (load_history(home_dir) == -1)
	{
		printf("Could not find %s at %s when trying to load history.\n", HIST_FILE_NAME, home_dir);
	}
	
	//Load aliases (8)
	struct AliasPair aliasPairs[MAX_ALIASES];
	int aliasLen = read_alias_file(home_dir, ALIASES_FILE_NAME, aliasPairs);
	if (aliasLen == -1)
		printf("Failed to open the file \"%s\" at \"%s\"\n", ALIASES_FILE_NAME, home_dir);
	if (aliasLen == -2)
		printf("Failed to parse a line in the file \"%s\" at \"%s\"\n", ALIASES_FILE_NAME, home_dir);
	if (aliasLen == -3)
		printf("Failed to add to the list of aliases. There are too many aliases. The limit is %d\n", MAX_ALIASES);
	if (aliasLen < 0) // reset count
		aliasLen = 0;

	// getting some memory for reading inputs and args
	char originInput[MAX_BUFFER_LENGTH];
	char recentInput[MAX_BUFFER_LENGTH];
	char backgroundInput[MAX_BUFFER_LENGTH];
	char* args[MAX_ARGS_QUANTITY];
	
	//Do while shell has not terminated
	while(1)
	{
		//Display prompt (1)
		display_prompt();

		//Read and parse user originInput (1)
		// reads originInput
		if (retrieve_input(originInput, MAX_BUFFER_LENGTH) == -1)
			break;

		// creates a copy for manipulation elsewhere
		strcpy(backgroundInput, originInput);
		strcpy(recentInput, originInput);

		// parses originInput using copy
		memset(args, 0, MAX_ARGS_QUANTITY * sizeof(char*));
		int argsLen = parse_input(backgroundInput, args);
		if (argsLen <= 0) continue;

		// linked list to store all iterated commands, used to look for cycles
		LinkedList list = NULL;

		// loop until an error occurs, the max iterations occur, or it naturally ends
		int error = 0;
		while (1)
		{
			// the command has been repeated
			if (contains(recentInput, list) == 0)
			{
				printf("Could not run the command as a cycle had occured.\n");
				error = -1;
				break;
			}

			// adding it to the list so we can check if it is repeated later
			ListNode* node;
			node = (ListNode*)malloc(sizeof(ListNode*));
			node->command = (char*)malloc(sizeof(char) * MAX_BUFFER_LENGTH);
			strcpy(node->command, recentInput);
			add_node(node, &list);

			// making a history invocation if it is one
			if (is_history_invocation(backgroundInput) == 0)
			{
				if (argsLen == 1)
				{
					char* history_invocation = NULL;
					int historyResult = invoke_from_history(backgroundInput, args[0], &history_invocation); // 0 = success, -1 = fail, 1 = not an invocation
					if (historyResult == 0)
					{
						// If it's a history invocation, replace the command with the history command
						strcpy(backgroundInput, history_invocation);
						strcpy(recentInput, backgroundInput);
						argsLen = parse_input(backgroundInput, args);
					}
					else if (historyResult == -1)
					{
						error = -1;
						break;
					}
				}
				else
				{
					printf("history invocation should have no arguments.\n");
					error = -1;
					break;
				}

			// replacing relevant alias if it is one
			}
			else if (argsLen > 0 && index_of_alias(args[0], aliasPairs, aliasLen) != -1)
			{
				// if we find the alias with the first argument, re-process the previous process
				int aliasIndex = index_of_alias(args[0], aliasPairs, aliasLen);
				if (argsLen > 1)
				{
					// get the length of the first argument and add everything else from the input line
					// consequently reconstructing the line to fit expectations
					int len = 0;
					while (*(*args + len) != '\0')
					{
						len++;
					}
					strcpy(backgroundInput, (aliasPairs + aliasIndex)->command);
					strcat(backgroundInput, recentInput + len);
				}
				else
				{
					strcpy(backgroundInput, (aliasPairs + aliasIndex)->command);
				}
				strcpy(recentInput, backgroundInput);
				argsLen = parse_input(backgroundInput, args);
			
			// normal command/rubbish so can end this
			}
			else
			{
				break;
			}
		}

		// freeing list
		while (list != NULL) {
			free(list->command);
			ListNode* next = list->next;
			free(list);
			list = next;
		}

		// if the command is not a history invocation, add it to history
		if (is_history_invocation(originInput) != 0) add_to_history(originInput);

		// if any errors occur, end this command execution
		if (error != 0) continue;

		if (strcmp("exit", args[0]) == 0) break;
		if (strcmp("getpath", args[0]) == 0)
		{
			if (argsLen > 1)
			{
				printf("getpath should have no arguments.\n");
			}
			else
			{
				char* path = GetPathEnv();
				printf("%s\n", path);
				free(path);
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
				ChangePathEnv(newPath);
				printf("New path changed to %s\n", newPath);
			}
		}
		else if (strcmp("cd", args[0]) == 0)
		{
			if (argsLen == 1)
			{
				ChangeDirectory(home_dir);
			}
			else if(argsLen == 2)
			{
				ChangeDirectory(args[1]);
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
				// Print the history
				print_history();
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
			else if (argsLen >= 3)
			{
				// creates a copy for manipulation elsewhere
				char* inputCopy = (char*)malloc(MAX_BUFFER_LENGTH * sizeof(char));
				strcpy(inputCopy, recentInput);

				// parses originInput using copy
				char** aliasArgs = (char**)calloc(2, sizeof(char*));
				if (parse_alias_line(&inputCopy[6], aliasArgs) == 0)
				{
					int tempLen = add_alias(aliasArgs[0], aliasArgs[1], aliasPairs, aliasLen);
					if (tempLen == -1) {
						printf("Could not add alias \"%s\" to the list since there are too many aliases.\n", aliasArgs[0]);
					}
					else
					{
						aliasLen = tempLen;
						printf("Successfully added alias \"%s\" with command \"%s\"\n", aliasArgs[0], aliasArgs[1]);
					}
				}
				else
				{
					printf("Could not parse command. Please separate the alias and command with a space.\n");
				}
			}
			else
			{
				printf("Alias cannot accept only one argument.\n");
			}
		}
		else if (strcmp("unalias", args[0]) == 0)
		{
			if (argsLen == 2)
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
			else
			{
				printf("Unalias can only accept exactly one argument.\n");
			}
		}
		else if (argsLen > 1 && strcmp("clear", args[0]) == 0 && strcmp("history", args[1]) == 0)
		{
			if (argsLen == 2)
			{
				if (clear_history(home_dir) == -1)
				{
					printf("Error: Failed to open history file for writing.\n");
				}
				else
				{
					printf("History cleared.\n");
				}
			}
			else
			{
				printf("clear history does not accept arguments.\n");
			}
		}
		else 
		{
			execute_external_command(args);
		}
	}
	// End while (okay yes this comment is pointless)
	
	//Save history (6)
	if (save_history(home_dir) == -1)
	{
		printf("Could not write to %s at %s when trying to save history.\n", HIST_FILE_NAME, home_dir);
	}
	
	//Save aliases (8)
	if (set_alias_file(home_dir, ALIASES_FILE_NAME, aliasPairs, aliasLen) == -1)
		printf("Failed to add aliases to the file \"%s\" at \"%s\"\n", ALIASES_FILE_NAME, home_dir);
	
	//Restore original path (3)
	ChangePathEnv(saved_path);
	printf("Path restored: %s\n", GetPathEnv());
	
	//Exit
	return 0;
}