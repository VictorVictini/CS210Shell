#include "directory_path_manipulation.h"

int change_working_directory(const char* path)
{
    return chdir(path);
}

void get_home_directory(char* home)
{
    strncpy(home, getenv("HOME"), MAX_PATH_LENGTH - 1);
    home[MAX_PATH_LENGTH - 1] = '\0';
}

int change_path_env(const char* path)
{
    return setenv("PATH", path, 1);
}

void get_path_env(char* path)
{
    strncpy(path, getenv("PATH"), MAX_PATH_LENGTH - 1);
    path[MAX_PATH_LENGTH - 1] = '\0';
}

int change_directory(char* dir)
{
    if(chdir(dir) != 0)
    {
        perror(dir);
        return -1;
    }
    return 0;
}