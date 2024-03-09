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
	
	//Load aliases (8)
	
	//Do while shell has not terminated
	while(1)
	{
		//Display prompt (1)
		display_prompt();

		//Read and parse user input (1)
		// reads input
		char* input = (char*)malloc(MAX_BUFFER_LENGTH * sizeof(char));
		if (retrieve_input(input, MAX_BUFFER_LENGTH) == -1) break;

		// creates a copy for manipulation elsewhere
		char* inputClone = (char*)malloc(MAX_BUFFER_LENGTH * sizeof(char));
		strcpy(inputClone, input);

		// parses input using copy
		char** args = (char**)calloc(MAX_ARGS_QUANTITY, sizeof(char*));
		int argsLen = parse_input(inputClone, args, MAX_ARGS_QUANTITY);
		
		if (argsLen > 0)
		{
			if (strcmp("exit", args[0]) == 0) break;
			
			//While the command is a history invocation or alias then replace it 
			//with the appropriate command from history or the aliased command 
			//respectively (5 & 7)

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
			else 
			{
				execute_external_command(args);
			}
		}
		
		free(input); //frees the buffer (stage_1.c)
		free(inputClone); //frees the buffer (stage_1.c)
		free(args); //frees the result (stage_1.c)
	}
	// End while (okay yes this comment is pointless)
	
	//From here down *could* be a separate exit function, depends on your logic
	//Save history (6)
	
	//Save aliases (8)
	
	//Restore original path (3)
	ChangePathEnv(saved_path);
	printf("Path restored: %s\n", GetPathEnv());
	
	//Exit
	return 0;
} 
