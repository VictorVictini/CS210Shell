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
	for (int i = 0; i < MAX_ALIASES; i++) {
		(aliasPairs + i)->alias = (char*)calloc(sizeof(char), MAX_BUFFER_LENGTH);
		(aliasPairs + i)->command = (char*)calloc(sizeof(char), MAX_BUFFER_LENGTH);
	}
	int aliasLen = read_alias_file(home_dir, ALIASES_FILE_NAME, aliasPairs);
	if (aliasLen == -1) printf("Failed to open the file \"%s\" at \"%s\"\n", ALIASES_FILE_NAME, home_dir);
	if (aliasLen == -2) printf("Failed to parse a line in the file \"%s\" at \"%s\"\n", ALIASES_FILE_NAME, home_dir);
	if (aliasLen == -3) printf("Failed to add to the list of aliases. There are too many aliases. The limit is %d\n", MAX_ALIASES);
	if (aliasLen < 0) aliasLen = 0;

	// getting some memory for reading inputs and args
	char* input = (char*)malloc(MAX_BUFFER_LENGTH * sizeof(char));
	char* inputClone = (char*)malloc(MAX_BUFFER_LENGTH * sizeof(char));
	char** args = (char**)malloc(MAX_ARGS_QUANTITY * sizeof(char*));
	
	//Do while shell has not terminated
	while(1)
	{
		//Display prompt (1)
		display_prompt();

		//Read and parse user input (1)
		// reads input
		if (retrieve_input(input, MAX_BUFFER_LENGTH) == -1) break;

		// creates a copy for manipulation elsewhere
		strcpy(inputClone, input);

		// parses input using copy
		memset(args, 0, MAX_ARGS_QUANTITY * sizeof(char*));
		int argsLen = parse_input(inputClone, args, MAX_ARGS_QUANTITY);

		if (argsLen > 0)
		{
			//While the command is a history invocation or alias then replace it 
			//with the appropriate command from history or the aliased command 
			//respectively (5 & 7)

			// Check for history invocations and handle them
			char* history_invocation = NULL;
			int historyResult = invoke_from_history(input, args[0], argsLen, &history_invocation); // 0 = success, -1 = fail, 1 = not an invocation
			if (historyResult == 0)
			{
				// If it's a history invocation, replace the command with the history command
				argsLen = parse_input(history_invocation, args, MAX_ARGS_QUANTITY);
			}
			else if (historyResult == -1) continue;

			// if we find the alias with the first argument, re-process the previous process
			int aliasIndex = index_of_alias(args[0], aliasPairs, aliasLen);
			if (aliasIndex != -1) {
				if (argsLen > 1) {
					// get the length of the first argument and add everything else from the input line
					// consequently reconstructing the line to fit expectations
					int len = 0;
					while (*(*args + len) != '\0') {
						len++;
					}
					strcpy(inputClone, (aliasPairs + aliasIndex)->command);
					strcat(inputClone, input + len);
				} else {
					strcpy(inputClone, (aliasPairs + aliasIndex)->command);
				}
				
				argsLen = parse_input(inputClone, args, MAX_ARGS_QUANTITY);
			}

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
				else if (argsLen > 2) // <-- TODO support folders with spaces
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
				else if(argsLen == 2) // <-- TODO support folders with spaces
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
					strcpy(inputCopy, input);

					// parses input using copy
					char** aliasArgs = (char**)calloc(2, sizeof(char*));
					if (parse_alias_line(inputCopy + 6, aliasArgs) == 0) { // inputCopy + 6 skips "alias "
						int tempLen = add_alias(aliasArgs[0], aliasArgs[1], aliasPairs, aliasLen);
						if (tempLen == -1) {
							printf("Could not add alias \"%s\" to the list since there are too many aliases.\n", aliasArgs[0]);
						} else {
							aliasLen = tempLen;
							printf("Successfully added alias \"%s\" with command \"%s\"\n", aliasArgs[0], aliasArgs[1]);
						}
					} else {
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
					int tempLen = remove_alias(input + 8, aliasPairs, aliasLen);
					if (tempLen != -1) { // input + 8 skips "unalias "
						aliasLen = tempLen;
						printf("Successfully removed alias \"%s\"\n", input + 8);
					} else {
						printf("Could not find provided alias \"%s\".\n", input + 8);
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
	}
	// End while (okay yes this comment is pointless)
	
	//Save history (6)
	if (save_history(home_dir) == -1)
	{
		printf("Could not write to %s at %s when trying to save history.\n", HIST_FILE_NAME, home_dir);
	}
	
	//Save aliases (8)
	if (set_alias_file(home_dir, ALIASES_FILE_NAME, aliasPairs, aliasLen) == -1) printf("Failed to add aliases to the file \"%s\" at \"%s\"\n", ALIASES_FILE_NAME, home_dir);
	
	//Restore original path (3)
	ChangePathEnv(saved_path);
	printf("Path restored: %s\n", GetPathEnv());
	
	//Exit
	return 0;
}