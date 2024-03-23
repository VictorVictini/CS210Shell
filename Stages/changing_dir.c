#include "changing_dir.h"

void ChangeDirectory(char* input)
{
    if(chdir(input) != 0)
        perror(input);
}
