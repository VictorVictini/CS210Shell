#include "shell.h"

int main(){
	//Find the user home directory from the environment (3)
	
	//Save the current path (3)

	//Set current working directory to user home directory (3)
	
	//Load history (6)
	
	//Load aliases (8)
	
	//Do while shell has not terminated
	while(1){
		//Display prompt (1)
		display_prompt();

		//Read and parse user input (1)
		char** args = ParseInput();
		if (args == NULL) break;

		// for testing purposes
		for (int i = 0; *(args + i) != NULL; i++) {
			printf("%s\n", *(args + i));
		}
		//While the command is a history invocation or alias then replace it 
		//with the appropriate command from history or the aliased command 
		//respectively (5 & 7)
		
		//If command is built-in invoke appropriate function (1-5, 7)
		
		//(Nat): this bit is just a placeholder to make sure the external_command goes through; replace this specific execute_external_command with "built-in invoke appropriate function" later
		if (1) {
			execute_external_command(args);
		}
		
		//Else execute command as an external process (2)
		else {
        		execute_external_command(args);
   		 }

		free(args);
	}
	// End while (okay yes this comment is pointless)
	
	//From here down *could* be a separate exit function, depends on your logic
	//Save history (6)
	
	//Save aliases (8)
	
	//Restore original path (3)
	
	//Exit
	return 0;
}