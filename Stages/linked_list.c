#include "linked_list.h"

void add_node(ListNode* node, LinkedList* list)
{
    node->next = *list;
    *list = node;
}

int contains(char* target, LinkedList list)
{
    ListNode* temp = list;
    while (temp != NULL)
    {
        if (strcmp(target, temp->command) == 0)
            return 0;

        temp = temp->next;
    }
    return -1;
}