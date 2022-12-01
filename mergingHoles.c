/**
 * File: mergingHoles.c
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
 * This file helps merge adjacent holes into one hole.
 *
 */

#include "linked_list.h"
#include <stdlib.h>
#include "sorting.h"

/**
 * mergeFreeBlocks
 *
 * @param lp        linked list pointer
 *
 * This function merges adjacent holes into one hole.
 */
void mergeFreeBlocks(List* lp) {
  Node* node;
  List* newListP;
  newListP = (List*)malloc(sizeof(List));
  initList(newListP);

  List* newListH;
  newListH = (List*)malloc(sizeof(List));
  initList(newListH);

  // Divide P and H into separated nodes.
  node = lp->head;
  while(node != NULL) {
    if (node->process[0] == 'P') {
      addAtLimit(newListP, node->process, node->base, node->limit);
    }
    node = node->next;
  }

  node = lp->head;
  while(node != NULL) {
    if (node->process[0] == 'H') {
      addAtLimit(newListH, node->process, node->base, node->limit);
    }
    node = node->next;
  }

  // Set base as same number when they are connected each other
  Node* nodeH;
  nodeH = newListH->head;
  int holeSize = 0;
  int defaultBase = 0;
  int holeCnt = 0;

  while(nodeH != NULL) {
    if(holeCnt == 0) {
      defaultBase = nodeH->base;
      holeSize = nodeH->limit;
      holeCnt++;
      nodeH = nodeH->next;
    } else {
      if((holeSize + defaultBase) == nodeH->base) {
        nodeH->base = defaultBase;
        holeSize += nodeH->limit;
        nodeH->limit = holeSize;
        holeCnt++;
        nodeH = nodeH->next;
      } else {
        defaultBase = nodeH->base;
        holeSize = nodeH->limit;
        holeCnt++;
        nodeH = nodeH->next;
      }
    }
  }

  // Copy H nodes into new node to merge operation.
  List* newListH2;
  newListH2 = (List*)malloc(sizeof(List));
  initList(newListH2);

  nodeH = newListH->head;
  while(nodeH != NULL) {
    addAtLimit(newListH2, nodeH->process, nodeH->base, nodeH->limit);
    nodeH = nodeH->next;
  }

  // Detecting adjacent holes and remove unnecessary holes.
  holeCnt = 0;
  int removeCnt = 0;
  nodeH = newListH->head;
  while(nodeH != NULL) {
    if(holeCnt == 0) {
      defaultBase = nodeH->base;
      holeCnt++;
      nodeH = nodeH->next;
    } else {
      if(nodeH->base == defaultBase) {
        removeFromIndex(newListH2, holeCnt - 1 - removeCnt);
        defaultBase = nodeH->base;
        removeCnt++;
        holeCnt++;
        nodeH = nodeH->next;
      } else {
        defaultBase = nodeH->base;
        holeCnt++;
        nodeH = nodeH->next;
      }
    }
  }

  List* newList2;
  newList2 = (List*)malloc(sizeof(List));
  initList(newList2);

  node = newListP->head;
  while(node != NULL) {
    addAtLimit(newList2, node->process, node->base, node->limit);
    node = node->next;
  }

  node = newListH2->head;
  while(node != NULL) {
    addAtLimit(newList2, node->process, node->base, node->limit);
    node = node->next;
  }
  sorting(newList2);

  // Changing pointer from temporary lp to original lp.
  lp->head = newList2->head;

  free(newListP);
  free(newListH);
  free(newListH2);
}