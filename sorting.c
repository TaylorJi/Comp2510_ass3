/**
 * File: sorting.c
 *
 * Author: Nash Baek (A01243888, nash4comp@gmail.com)
 *         Dongil Kwon (A01267744, dikwon79@naver.com)
 *         Junho Han (A01061045, junhohan2@gmail.com)
 *         Taylor Ji (A01304056, sji24@my.bcit.ca)
 * Date: 1st December, 2022
 * Course: COMP2510
 *
 * Summary of File:
 *
 * This file helps to sort linked list by using recursive method.
 * The node data is sorted and missed holes are added.
 */

#include "linked_list.h"
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * merge
 *
 * @param head1 one pointer for sorting
 * @param head2 the other pointer for sorting
 * @return return new node with sorting
 *
 * This function compares the fragmented data
 * and connects sorted nodes in order.
 */
struct Node* merge(Node * head1, Node * head2) {
  Node* result = NULL;
  if(head1 == NULL) {
    return (head2);
  } else if(head2 == NULL) {
    return (head1);
  }

  if (head1->base < head2->base) {
    result = head1;
    result->next = merge(head1->next, head2);
  }
  else if(head1->base == head2->base){
    printf("duplicate base error");
    exit(-1);
  } else {
    result = head2;
    result-> next = merge(head1, head2->next);
  }
  return (result);
}

/**
 * holesum
 *
 * @param list  new pointer to make new node
 * @param list2  original pointer
 *
 * This function is to fill in the hole that fell out.
 *           and Check duplicate process values
 */
void holesum(Node * list, List* list2) {
  List* newNode;
  newNode = (List*)malloc(sizeof(List));
  initList(newNode);
  int base;
  if(list->base !=0) {
    base = 0;
  } else{
    base = list->base;
  }
  int limit=0;
  struct Node* next;
  char buffer[50];
  int i =0;
  while(list != NULL) {
    if (list->process[0] != 'H') {
      for (int j = 0; j <= i; j++) {
        if (buffer[j] == list->process[1]) {
          printf("duplicate process error");
          exit(-1);
        }
      }
      buffer[i] = list->process[1];
      i++;
    }
    if(list->base - limit != base ) {
      addAtLimit(newNode, "H",  base + limit, list->base - (base+limit));
    }
    addAtLimit(newNode, list->process,  list->base, list->limit);
    base = list->base;
    limit = list->limit;
    list = list->next;
  }
  list2->head = newNode->head;
  free(newNode);
}

/**
 * getLength
 *
 * @param newmainList is data node to get the size
 * return count : total node count
 * This function gets the lenth of the linked list.
 */
int getLength(Node* newmainList) {
  int count = 0;
  Node* mainList = newmainList;
  while(mainList != NULL) {
    count++;
    mainList = mainList->next;
  }
    return count;
}

/**
 * mergeSort
 *
 * @param lp pointer of original node
 * @param lp size of total node
 * Return the truncated data to merge.
 *
 * This function truncates all the data and sends it as a merge function for comparison.
 */
struct Node* mergeSort(Node* lp,int size){
  Node* head1 = lp;
  int mid = size / 2;
  if(head1->next == NULL) {
    return head1;
  }
  while(mid - 1 > 0) {
    head1 = head1->next;
    mid--;
  }
  Node* head2 = head1->next;
  head1->next = NULL;
  head1 = lp;
  if (head1->process == head2->process){
    printf("error");
    exit(-1);
  }
  Node* h1 = mergeSort(head1, getLength(head1));
  Node* h2 = mergeSort(head2, getLength(head2));
  return merge(h1, h2);
}

/**
 * sorting
 *
 * @param lp pointer to sort the node
 *
 * This function is the top-level call function that sort and fill the missing hole.
 */
void sorting(List* lp) {
 Node* node1 = lp->head;
 holesum(mergeSort(node1, getLength(node1)),lp);
}