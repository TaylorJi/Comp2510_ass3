#ifndef COMP2510ASSIGNMENT3_SORTING_H
#define COMP2510ASSIGNMENT3_SORTING_H

#include "linked_list.h"

Node* sorting(List* lp);

struct Node* mergeSort(Node* lp,int size);
Node *holesum(Node *list, List *ptr);

#endif //COMP2510ASSIGNMENT3_SORTING_H