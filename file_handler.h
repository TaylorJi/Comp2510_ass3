#ifndef FILE_POINTER
#define FILE_POINTER

#include <stdio.h>
#include "linked_list.h"

FILE* fileOpen(FILE* fp, char* filename, char* type);
void fileClose(FILE* fp);
FILE* loadFile();
FILE* addIntoLinkedList(FILE* fp, List* lp);
int sanityCheck(char* process, int base, int limit, int retScanf);
void errorMsg(int sanityCode);

#endif