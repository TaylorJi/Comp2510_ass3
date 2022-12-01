/**
 * File: linked_list.c
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
 * This file provides functions related linked list such as
 * creating, adding, removing and printing.
 *
 */

#include <stddef.h>
//#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

/**
 * initList
 *
 * @param lp        linked list pointer
 *
 * This function initializes linked list pointer with NULL value.
 */
void initList(List *lp) {
  lp->head = NULL;
  lp->tail = NULL;
  lp->cnt = 0;
}

/**
 * createNode
 *
 * @param process   the process data
 * @param base      the base data
 * @param limit     the limit data
 * @return the node which is firstly created by this function
 *
 * This function creates nodes for empty node.
 */
Node* createNode(char* process, int base, int limit) {
  Node* newNode;
  newNode = (Node*)malloc(sizeof(Node));
  strcpy(newNode->process, process);
  newNode->base = base;
  newNode->limit = limit;
  newNode->next = NULL;
  return newNode;
}

/**
 * addAtBase
 *
 * @param lp        linked list pointer
 * @param process   the process data
 * @param base      the base data
 * @param limit     the limit data
 *
 * This function adds a node at the beginning of the list.
 */
void addAtBase(List* lp, char* process, int base, int limit) {
  Node* node;
  node = createNode(process, base, limit);

  // If current List is empty
  if(lp->head == NULL) {
    lp->head = node;
    lp->tail = node;
  } else { // If current List is not empty
    node->next = lp->head;
    lp->head = node;
  }
  lp->cnt++;
}

/**
 * addAtLimit
 *
 * @param lp        linked list pointer
 * @param process   the process data
 * @param base      the base data
 * @param limit     the limit data
 *
 * This function adds a node at the end of the list.
 */
void addAtLimit(List* lp,char* process, int base, int limit) {
  Node* node;
  node = createNode(process, base, limit);

  // If current List is empty
  if(lp->head == NULL) {
    lp->head = node;
    lp->tail = node;
  } else { // If current List is not empty
    lp->tail->next = node;
    lp->tail = lp->tail->next;
  }
  lp->cnt++;
}

/**
 * removeFromBase
 *
 * @param lp        linked list pointer
 * @return -1 if the list is empty, 0 if the removal work was successfully done.
 * This function removes node at the beginning of the list.
 */
int removeFromBase(List* lp) {
  if(lp->head == NULL) {
    printf("Error! Asked List is empty.\n");
    return -1;
  } else {
    lp->head = lp->head->next;
    lp->cnt--;
  }
  return 0;
}

/**
 * removeFromLimit
 *
 * @param lp        linked list pointer
 * @return -1 if the list is empty, 0 if the removal work was successfully done.
 * This function removes node at the end of the list.
 */
int removeFromLimit(List* lp) {
  Node* temp;
  if(lp->tail == NULL) {
    printf("Error! Asked List is empty.\n");
    return -1;
  } else {
    temp = lp->head;
    while(temp->next != lp->tail) {
      temp = temp->next;
    }
    lp->tail = temp;
    lp->tail->next = NULL;
    lp->cnt--;
  }
  return 0;
}

/**
 * removeFromIndex
 *
 * @param lp        linked list pointer
 * @param index     the number of index to be removed
 * @return 0 if the removal work was successfully done.
 * This function removes node at the end of the list.
 */
int removeFromIndex(List* lp, int index) {
  Node* temp = lp->head; // Creating a temporary
  // variable pointing to head
  int i;
  if (index == 0) {
    lp->head = lp->head->next; // Advancing the head pointer
    temp->next = NULL;
    lp->cnt--;
    free(temp); // Node is deleted
  }
  else {
    for (i = 0; i < index - 1; i++) {
      temp = temp->next;
    }
    temp->next = temp->next->next;
    lp->cnt--;
  }
  return 0;
}

/**
 * printList
 *
 * @param lp        linked list pointer
 *
 * This function prints out all of the linked list on the screen.
 */
void printList(List* lp) {
  if(lp->head == NULL) {
    printf("This List is empty.\n");
    return;
  }
  Node* node;
  node = lp->head;
  while(node != NULL) {
    printf("%s %d %d", node->process, node->base, node->limit);
    node = node->next;
    if(node != NULL) {
      printf("\n");
    }
  }
}
