#include "strutils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  // init section
  size_t l = 0;
  size_t l2 = 0;
  char* testS = strdup("the quick brown fox jumps over the lazy dog");
  char* testS2 = strdup("this is a test string, for testing purposes, on a testing file");
  char** testS_split = strsplit(testS, ' ', &l);
  char** testS2_split = strsplit(testS2, ',', &l2);
  char* testRS = strinvert(strdup("string to be reversed"));

  // allocation section
  char* toPrint = malloc(256);
  char* toPrint2 = malloc(256);
  sprintf(toPrint, "%s %s %s %s under %s %s %s", testS_split[0], testS_split[2], testS_split[l-1], testS_split[4], testS_split[6], testS_split[l-2], testS_split[3]);
  sprintf(toPrint2, "%s,%s,%s", testS2_split[0], testS2_split[2], testS2_split[1]);

  // I/O section
  printf("%s: %s\n", testS, toPrint);
  printf("%s: %s\n", testS2, toPrint2);
  printf("string to be reversed: %s\n", testRS);

  // freeing section
  cdptrfree(testS_split, l);
  cdptrfree(testS2_split, l2);
  free(toPrint);
  free(testS);
  free(toPrint2);
  free(testS2);
  free(testRS);

  return 0;
}