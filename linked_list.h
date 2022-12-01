#ifndef COMP2510ASSIGNMENT3_LINKED_LIST_H
#define COMP2510ASSIGNMENT3_LINKED_LIST_H

typedef struct Node {
    char process[10];
    int base;
    int limit;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int cnt;
} List;

void initList(List *lp);
Node* createNode(char* process, int base, int limit);
void addAtBase(List* lp, char* process, int base, int limit);
void addAtLimit(List* lp, char* process, int base, int limit);
int removeFromBase(List* lp);
int removeFromLimit(List* lp);
int removeFromIndex(List* lp, int index);
void printList(List* lp);

#endif //COMP2510ASSIGNMENT3_LINKED_LIST_H
