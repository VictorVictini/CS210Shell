#include "stage_9.h"

int contains(char* target, char** list, int len) {
    for (int i = 0; i < len; i++) {
        if (strcmp(target, *(list + i)) == 0) return 0;
    }
    return -1;
}