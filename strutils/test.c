#include "strutils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char* testS = strdup("the quick brown fox jumps over the lazy dog");
  size_t l = 0;
  char** testS_split = strsplit(testS, ' ', &l);
  char* toPrint = malloc(256);
  sprintf(toPrint, "%s %s %s %s under %s %s %s", testS_split[0], testS_split[2], testS_split[l-1], testS_split[4], testS_split[6], testS_split[l-2], testS_split[3]);
  printf("%s\n", toPrint);
  cdptrfree(testS_split, l);
  free(toPrint);
  free(testS);
  return 0;
}