#include "stage_3.h"

char* GetWorkingDirectory()
{
	char* cwd = (char*)calloc(MAX_PATH_LENGTH, sizeof(char*));
	getcwd(cwd, MAX_PATH_LENGTH);
	return cwd;
}

int ChangeWorkingDirectory(const char* path)
{
	return chdir(path);
}

char* GetHomeDirectory()
{
	return getenv("HOME");
}