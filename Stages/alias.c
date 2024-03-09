#include "alias.h"

int add_alias(char* alias, char* command, struct AliasPair* aliasPairs, int len) {
    // checking the current amount
    int aliasIndex = index_of_alias(alias, aliasPairs, len);
    if (len > MAX_ALIASES) return -1;
    if (len == MAX_ALIASES && aliasIndex == -1) return -1;

    // if it was found, we replace its command
    if (aliasIndex != -1) {
        (aliasPairs + aliasIndex)->command = command;
        return len;
    }

    // adds a new aliasPair
    struct AliasPair newPair = {alias, command};
    *(aliasPairs + len) = newPair;
    return len + 1;
}

int remove_alias(char* alias, struct AliasPair* aliasPairs, int len) {
    // if the alias does not exist in the pairs, also acts as a length check
    int index = index_of_alias(alias, aliasPairs, len);
    if (index == -1) return -1;

    // swap the given index with the last 'filled' index then set the last 'filled' index's values to null
    // this process is combined for efficiency
    *(aliasPairs + index) = *(aliasPairs + len - 1);
    (aliasPairs + len - 1)->command = NULL;
    (aliasPairs + len - 1)->alias = NULL;
    return len - 1;
}

int index_of_alias(char* alias, struct AliasPair* aliasPairs, int len) {
    for (int i = 0; i < len; i++) {
        if (strcmp((aliasPairs + i)->alias, alias) == 0) return i;
    }
    return -1;
}

void print_alias(struct AliasPair* aliasPairs, int len) {
    for (int i = 0; i < len; i++) {
        printf("\"%s\" is an alias for \"%s\"\n", (aliasPairs + i)->alias, (aliasPairs + i)->command);
    }
}