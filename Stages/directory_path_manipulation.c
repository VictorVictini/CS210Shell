#include "directory_path_manipulation.h"

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
    char* home = (char*)calloc(MAX_PATH_LENGTH, sizeof(char*));
    strcpy(home, getenv("HOME"));

    return home;
}

int ChangePathEnv(const char* path)
{
    return setenv("PATH", path, 1);
}

char* GetPathEnv()
{
    char* path = (char*)calloc(MAX_PATH_LENGTH, sizeof(char*));
    strcpy(path, getenv("PATH"));

    return path;
}