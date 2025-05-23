#include "strutils.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char** strsplit(char* s, char d, size_t* lr) {
  char* w = strtok(s, &d);
  char** v = malloc(sizeof(char*));
  if (v == NULL){
    free(v);
    return NULL;
  }
  size_t l = 0;
  while (w != NULL) {
    l++;
    v = realloc(v, l * sizeof(char*));
    if (v == NULL) {
      for (size_t i = 0; i < l; i++) free(v[i]);
      free(v);
      return NULL;
    }
    v[l - 1] = strdup(w);
    w = strtok(NULL, &d);
  }
  *lr = l;
  return v;
}

void cdptrfree(char** l, size_t ln) {
  for (size_t i = 0; i < ln; i++)
    free(l[i]);
  free(l);
}