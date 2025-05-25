#include "strutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  // oh my fucking god what am i doing
  size_t l = 0;
  size_t l2 = 0;
  char* testS = strdup("the quick brown fox jumps over the lazy dog");
  char* testS2 = strdup("this is a test string, for testing purposes, on a testing file");
  char** testS_split = strsplit(testS, ' ', &l);
  char** testS2_split = strsplit(testS2, ',', &l2);
  char* testRS = strinvert(strdup("string to be reversed"));
  char* testTCS = strdup("this is title-cased text, this is also just a string/array of characters\\whatever you could call it");
  char* testUCS = strdup("i'm screaming at the very top of my lungs!!!!! can you hear me????");
  char* testRCS = strdup("I'M SCREAMING AT THE TOP OF MY VERY LUNGS!!!!! can you hear me????");
  char** testJS = malloc(sizeof(char*) * 3);
  testJS[0] = strdup("i'm");
  testJS[1] = strdup("going");
  testJS[2] = strdup("insane");
  char* testJdS = strjoin(testJS, 3, ' ');
  char* testTCdS = strtitlecase(testTCS);
  char* testUCdS = struppercase(testUCS);
  char* testLCdS = strlowercase(testUCdS);
  char* testRCdS = strreversecase(testRCS);

  // printing part
  printf("%s:\n%s %s %s %s under %s %s %s\n\n", testS, testS_split[0], testS_split[2], testS_split[l-1], testS_split[4], testS_split[6], testS_split[l-2], testS_split[3]);
  printf("%s:\n%s,%s,%s\n\n", testS2, testS2_split[0], testS2_split[2], testS2_split[1]);
  printf("string to be reversed:\n%s\n\n", testRS);
  printf("%s:\n%s\n\n", testTCS, testTCdS);
  printf("\"i'm\", \"going\", \"insane\":\n%s\n\n", testJdS);
  printf("%s:\n%s\n\n", testUCS, testUCdS);
  printf("%s:\n%s\n\n", testUCdS, testLCdS);
  printf("%s:\n%s\n", testRCS, testRCdS);

  // MMM hell
  cdptrfree(testS_split, l);
  cdptrfree(testS2_split, l2);
  cdptrfree(testJS, 3);
  free(testJdS);
  free(testS);
  free(testS2);
  free(testRS);
  free(testTCdS);
  free(testTCS);
  free(testUCdS);
  free(testUCS);
  free(testLCdS);
  free(testRCS);
  free(testRCdS);

  // peace.
  return 0;
}