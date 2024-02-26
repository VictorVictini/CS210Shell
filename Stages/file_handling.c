#include "file_handling.h"

int set_file(const char* file_location, char** data, const int len) {
    FILE* fptr = fopen(file_location, "w");
    if (fptr == NULL) return -1;
    for (int i = 0; i < len; i++) {
        fprintf(fptr, "%s\n", *(data + i));
    }
    fclose(fptr);
    return 0;
}

int get_file(const char* file_location, char** result, int max_lines) {
    FILE* fptr = fopen(file_location, "r");
    if (fptr == NULL) return -1;
    char* currLine;
    for (int i = 0; i < max_lines && fgets(currLine, MAX_LINE_LENGTH, fptr) != NULL; i++) {
        currLine[strcspn(currLine, "\n")] = '\0';
        strcpy(*(result + i), currLine);
    }
    fclose(fptr);
    return 0;
}