#ifndef LINKED_LIST
#define LINKED_LIST

// imports
#include <string.h>

// types for linked list
typedef struct Node {
    char* command;
    struct Node* next;
} ListNode;

typedef ListNode* LinkedList;

/*
    Adds a given node to the start of a given linkedlist
    inputs: a pointer to the node to add, a pointer to the linkedlist to add it to
    outputs: n/a
    side effects: functionality dependant on the linkedlist will change
    written by Danyal
*/
void add_node(ListNode* node, LinkedList* list);

/*
    Finds if the node value is in the linkedlist
    inputs: the node value (string/char*), the linked list
    outputs: 0 if found, otherwise -1
    side effects: n/a
    written by Danyal
*/
int contains(char* target, LinkedList list);

#endif