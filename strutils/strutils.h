#ifndef STRUTILS_H
#define STRUTILS_H

// returns an array of strings containing
// `s` split into smaller chunks by `d`
//
// `char* s`: string
//
// `char d`: delimiter
//
// `int* lr`: length return
char** strsplit(char* s, char d, unsigned long* lr);

// invert a string
//
// `char* s`: string
char* strinvert(char* s);

// free a double-pointer char (string array)
// variable
//
// `char** sa`: string array
//
// `size_t ln`: array length
void cdptrfree(char** sa, unsigned long ln);

#endif