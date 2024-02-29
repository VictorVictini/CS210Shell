#include "stage_4.h"

void ChangeDirectory(char* input)
{
    if(chdir(input) != 0)
        perror(input);
}
