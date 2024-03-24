#include "directory_path_manipulation.h"

int change_working_directory(const char* path)
{
    return chdir(path);
}

void get_home_directory(char* home)
{
    strcpy(home, getenv("HOME"));
    home[MAX_PATH_LENGTH - 1] = '\0';
}

int change_path_env(const char* path)
{
    return setenv("PATH", path, 1);
}

void get_path_env(char* path)
{
    strcpy(path, getenv("PATH"));
    path[MAX_PATH_LENGTH - 1] = '\0';
}