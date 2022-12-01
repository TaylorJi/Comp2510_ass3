/**
 * File: assignment3.c
 *
 * Author: Nash Baek (A01243888, nash4comp@gmail.com)
 *         Dongil Kwon (A01267744, dikwon79@naver.com)
 *         Junho Han (A01061045, junhohan2@gmail.com)
 *         Taylor Ji (A01304056, sji24@my.bcit.ca)
 * Date: 1st December, 2022
 * Course: COMP2510
 *
 * Summary of File:
 *    This file prompts four menus to the user from whom they take input,
 *    and the program executes according to the user's input.
 *    Prompt menus are the following:
 *       1. Load an input file
 *       2. Merge holes
 *       3. Compact memory
 *       4. Print memory view
 *       5. Exit the program
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "file_handler.h"
#include "linked_list.h"
#include "sorting.h"
#include "mergingHoles.h"
#include "compaction.h"

/**
 * printMemory
 *
 * @param lp    Linked list pointer
 *
 * This function prints current linked list.
 */
void printMemory(List* lp) {
  printList(lp);
}

/**
 * promptMemory
 *
 * @param lp    Linked list pointer
 *
 * This function prompts five menu to be performed.
 */
int promptMenu() {
  int option = 0;
  printf("1. Load an input file\n"
         "2. Merge holes\n"
         "3. Compact memory\n"
         "4. Print memory view\n"
         "5. Exit the program\n\n"
         "Please select the option for operation.\n"
         ">> ");
  if (scanf(" %d", &option) <= 0) {
    printf("\nError! Option has to be between 1 to 5.\n\n");
    exit(-1);
  }
  return option;
}

/**
 * main
 *
 * This function drives the program.
 */
int main() {
  int option = promptMenu();
  List *lp;
  lp = (List*)malloc(sizeof(List));
  initList(lp);
    while(1) {
      if (option == 5) {
          break;
      }
      switch(option) {
        case 1: // load an input file
          if (lp != NULL) {
            initList(lp);
          }
          fileClose(addIntoLinkedList(loadFile(), lp));
          sorting(lp);
          printf("\n\noperation successful\n\n");
          option = promptMenu();
          break;
        case 2: // merge holes
          mergeFreeBlocks(lp);
          printf("\n\noperation successful\n\n");
          option = promptMenu();
          break;
        case 3: // compact memory
          compaction(lp);
          sorting(lp);
          printf("\n\noperation successful\n\n");
          option = promptMenu();
          break;
        case 4: // print memory view
          printf("\n");
          printMemory(lp);
          printf("\n\noperation successful\n\n");
          option = promptMenu();
          break;
        default:
          printf("\nError! Option has to be between 1 to 5.\n\n");
          option = promptMenu();
          break;
      }
    }
    free(lp);
    return 0;
}
