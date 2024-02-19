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
		char** args = ParseInput();
		if (args == NULL)
		{
			printf("\n");
			break;
		}
		if (args[0] != NULL && strcmp("exit", args[0]) == 0) break;

		//While the command is a history invocation or alias then replace it 
		//with the appropriate command from history or the aliased command 
		//respectively (5 & 7)
		
		//If command is built-in invoke appropriate function (1-5, 7)
		if (args[0] != NULL && strcmp("getpath", args[0]) == 0)
		{
			if (args[1] != NULL) printf("getpath should have no arguments.\n");
			else
			{
				char* path = GetPathEnv();
				printf("%s\n", path);
				free(path);
			}
		}
		else if (args[0] != NULL && strcmp("setpath", args[0]) == 0)
		{
			if (args[1] == NULL) printf("No argument provided for setpath.\n");
			else if (args[2] != NULL) printf("Too many arguments provided for setpath.\n");
			else
			{
				char* newPath = args[1];
				ChangePathEnv(newPath);
				printf("New path changed to %s\n", newPath);
			}
		}
		//Else execute command as an external process (2)
		else
		{
        	execute_external_command(args);
		}
		
		free(*args); //frees the buffer (stage_1.c)
		free(args); //frees the result (stage_1.c)
	}
	
	//Save history (6)
	
	//Save aliases (8)
	
	//Restore original path (3)
	ChangePathEnv(saved_path);
	printf("Path restored: %s\n", GetPathEnv());
	
	//Exit
	return 0;
}