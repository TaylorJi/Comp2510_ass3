/**
 * File: file_handler.c
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
 * This file contains the functions regarding file open and close.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linked_list.h"
#include "file_handler.h"
#include "sorting.h"

/**
 * fileOpen
 *
 * @param fp        file pointer to work
 * @param filename  filename to work
 * @param type      "r" for read, "w" for write
 * @return file pointer of this stream
 *
 * This function opens file.
 */
FILE* fileOpen(FILE* fp, char* filename, char* type) {
  fp = fopen(filename, type);
  return fp;
}

/**
 * fileClose
 *
 * @param fp        file pointer to work
 *
 * This function closes file.
 */
void fileClose(FILE* fp) {
  fclose(fp);
}

/**
 * checkBaseLimit
 *
 * @parm lp         list pointer
 *
 * This function checks if the next node' base is equal to the sum of a preceding node's base and limit.
 */
void checkBaseLimit(List* lp) {
  Node* node = lp->head;
  int isElementPresent = 1;
  for (int i = 0; i < lp->cnt - 1; ++i) {
    int sum = node->base + node->limit;
    node = node->next;
    if(node->base != sum) {
      isElementPresent = 0;
    }
    if(isElementPresent == 0) {
      printf("\nError: file is corrupted\n ");
      loadFile();
    }
    if (node == NULL) {
      return;
    }
  }
}

/**
 * errorMsg
 *
 * @param sanityCode    error code from the input file
 * @return the file pointer to work
 *
 * This function shows error code and terminate the program.
 */
void errorMsg(int sanityCode) {
    printf("Error! File format is invalid.\n");
    printf("Code number %d\n", sanityCode);
    exit(-1);
}

/**
 * addIntoLinkedList
 *
 * @param fp    file pointer to work
 * @param lp    linked list pointer
 * @return the file pointer to work
 *
 * This function adds data from the file pointer into linked list.
 */
FILE* addIntoLinkedList(FILE* fp, List* lp) {
    char buffer[100];
    char process[100];
    int base = 0;
    int limit = 0;
    int dummy = 0;
    int sanityCode = 0;
    int retScanf = 0;
    while(fgets(buffer, 100, fp) != NULL) {
      // dummy will validate extra elements in the file, ret the number of variable field
      retScanf = sscanf(buffer, "%s %d %d %d", process, &base, &limit, &dummy);
      if(sanityCode != 0) {
          errorMsg(sanityCode);
      }
      if (retScanf != -1) {
        sanityCode = sanityCheck(process, base, limit, retScanf);
        addAtLimit(lp, process, base, limit);
      }
    }
  sorting(lp);
  checkBaseLimit(lp);
  return fp;
}

/**
 * sanityCheck
 *
 * @param fp    file pointer to work
 * @return the file pointer to work
 *
 * This function checks validity of the linked list which storing input data.
 */
int sanityCheck(char* process, int base, int limit, int retScanf) {
    // TODO Delete these two lines before demo.
    printf("scanning: %s %d %d\n", process, base, limit);

    // Processors must be capital letters, if not error
    if ((process[0] != 'P') && (process[0] != 'H')) {
      return -1;
    }

    // Hole starts with H and must not have any other num/char, only itself
    if ((process[0] == 'H') && (strlen(process) != 1)) {
      return -2;
    }

    // P must have the following number, if it only has P then error
    if ((process[0] == 'P') && (strlen(process) == 1)) {
      return -3;
    }

    // P must have the following number, 57 is the ASCII code for 9
    if (process[0] == 'P') {
      for (int i = 1; i < strlen(process); i++) {
        if ((process[i] < 48) || (process[i] > 57)) {
          return -4;
        }
      }
    }

    // only numbers are allowed for base, limit and the retScanf must be 3 processor, base, int
    // limit cannot be 0
    if ((retScanf != -1) && (retScanf != 3) || (limit == 0)){
      printf("\nretsc: %d, limit : %d\n", retScanf, limit);
      return -5;
    }

    if (process[0] != 'P' && process[0] != 'H') {
    process[strlen(process)-1] = '\0';
    }
  return 0;
}

/**
 * loadFile
 *
 * @return the file pointer to work
 *
 * This function opens file by user input.
 */
FILE* loadFile() {
  char fileName[50];
  while(1) {
    printf("\nType the file name.\n");
    printf(">> ");
    scanf("%s", &fileName);
    if (strchr(fileName, '.') != NULL) {
      // Validate if the file extension is .txt
      char *fileExtension = strrchr(fileName, '.');
      if (strcmp(fileExtension, ".txt") == 0) {
        FILE *fp = fileOpen(fp, fileName, "r");
        if (fp == NULL) {
          printf("\nError: Unable to open file!\n");
        } else {
          return fp;
        }
      } else {
        printf("\nError: file extension must be .txt\n");
      }
    } else {
      printf("\nError: file extension must be .txt\n");
    }
  }
}