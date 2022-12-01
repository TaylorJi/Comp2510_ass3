/**
 * File: compaction.c
 *
 * Author: Nash Baek (nash4comp@gmail.com)
 *         Dongil Kwon (dikwon79@naver.com)
 *         Junho Han (junhohan2@gmail.com)
 *         Taylor Ji (sji24@my.bcit.ca)
 * Date: 1st December, 2022
 * Course: COMP2510
 *
 * Summary of File:
 *
 * This file helps to move all holes into the end of list
 * After that, merges adjacent holes.
 *
 */

#include "linked_list.h"
#include <stdlib.h>
#include "sorting.h"
#include "mergingHoles.h"

/**
 * compaction
 *
 * @param lp    Linked list pointer
 *
 * This function moves all holes into the end of linked list.
 * After that, it merges holes.
 */
void compaction(List* lp) {
    Node* node;
    List* newList;
    newList = (List*)malloc(sizeof(List));
    initList(newList);
    node = lp->head;
    while(node != NULL) {
        if (node->process[0] == 'P') {
            addAtLimit(newList, node->process, node->base, node->limit);
        }
        node = node->next;
    }
    node = lp->head;
    while(node != NULL) {
        if (node->process[0] == 'H') {
            addAtLimit(newList, node->process, node->base, node->limit);
        }
        node = node->next;
    }
    int index = 0;
    Node* newNode;
    newNode = newList->head;
    while(newNode != NULL) {
        newNode->base = index;
        index += newNode->limit;
        newNode = newNode->next;
    }
    lp->head = newList->head;
    sorting(lp);
    mergeFreeBlocks(lp);
    free(newList);
}


