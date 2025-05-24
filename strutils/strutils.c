#include "strutils.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char** strsplit(char* s, char d, size_t* lr) {
  char* tmp = strdup(s);
  if (!tmp) return NULL;
  char* w = strtok(tmp, &d);
  char** v = malloc(sizeof(char*));
  if (!v){
    free(v);
    free(w);
    free(tmp);
    return NULL;
  }
  size_t l = 0;
  while (w != NULL) {
    l++;
    v = realloc(v, l * sizeof(char*));
    if (!v) {
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
  if (!tmp) return NULL;
  for (int i = l - 1; i >= 0; i--) {
    tmp[l - (i + 1)] = s[i];
  }
  tmp[l] = 0x00;
  return tmp;
}

char* strjoin(char** sa, size_t sal, char d) {
  size_t toalloc = 0;
  for (size_t i = 0; i < sal; i++)
    toalloc += strlen(sa[i]);
  toalloc += sal - 1;
  toalloc += 1;
  char* temp = malloc(toalloc);
  if (!temp) return NULL;
  temp[0] = 0x00;
  for (size_t i = 0; i < sal; i++) {
    strcat(temp, sa[i]);
    if (i < sal - 1) {
      temp[strlen(temp)] = d;
      temp[strlen(temp) + 1] = 0x00;
    }
  }
  return temp;
}

char* strtitlecase(char* s) {
  char* temp = strdup(s);
  if (temp[0] >= 0x61 && temp[0] <= 0x7a)
    temp[0] -= 0x20;
  for (size_t i = 0; i < strlen(temp); i++) {
    if (i > 0) {
      if (temp[i - 1] == ' ' || temp[i - 1] == '-' || temp[i - 1] == '/' || temp[i - 1] == '\\' || temp[i - 1] == '\n') {
        if (temp[i] >= 0x61 && temp[i] <= 0x7a)
          temp[i] -= 0x20;
      }
    }
  }
  return temp;
}

char* struppercase(char* s) {
  char* temp = strdup(s);
  for (size_t i = 0; i < strlen(temp); i++) {
    if (temp[i] >= 0x61 && temp[i] <= 0x7a)
      temp[i] -= 0x20;
  }
  return temp;
}

char* strlowercase(char* s) {
  char* temp = strdup(s);
  for (size_t i = 0; i < strlen(temp); i++) {
    if (temp[i] >= 0x41 && temp[i] <= 0x5a)
      temp[i] += 0x20;
  }
  return temp;
}

void cdptrfree(char** sa, size_t ln) {
  for (size_t i = 0; i < ln; i++)
    free(sa[i]);
  free(sa);
}