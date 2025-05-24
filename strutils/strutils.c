#include "strutils.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char** strsplit(char* s, char d, size_t* lr) {
  char* tmp = strdup(s);
  if (tmp == NULL) return NULL;
  char* w = strtok(tmp, &d);
  char** v = malloc(sizeof(char*));
  if (v == NULL){
    free(v);
    free(w);
    free(tmp);
    return NULL;
  }
  size_t l = 0;
  while (w != NULL) {
    l++;
    v = realloc(v, l * sizeof(char*));
    if (v == NULL) {
      for (size_t i = 0; i < l; i++) free(v[i]);
      free(v);
      free(w);
      free(tmp);
      return NULL;
    }
    v[l - 1] = strdup(w);
    w = strtok(NULL, &d);
  }
  *lr = l;
  free(tmp);
  return v;
}

char* strinvert(char* s) {
  size_t l = strlen(s);
  char* tmp = malloc(l);
  if (tmp == NULL) return NULL;
  for (int i = l - 1; i >= 0; i--) {
    tmp[l - (i + 1)] = s[i];
  }
  tmp[l] = 0x00;
  return tmp;
}

void cdptrfree(char** sa, size_t ln) {
  for (size_t i = 0; i < ln; i++)
    free(sa[i]);
  free(sa);
}