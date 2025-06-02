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

// free a double-pointer variable
// variable
//
// `void** sa`: double-pointer
//
// `size_t ln`: array length
void dptrfree(void** dp, unsigned long ln);

// the polar opposite of `strsplit`
//
// `char** sa`: string array
//
// `size_t sal`: string array length
//
// `char d`: delimiter
char* strjoin(char** sa, unsigned long sal, char d);

// title-case a string
//
// `char* s`: string
char* strtitlecase(char* s);

// uppercase a string
//
// `char* s`: string
char* struppercase(char* s);

// lowercase a string
//
// `char* s`: string
char* strlowercase(char* s);

// `strlowercase` and `struppercase`
// in one function
//
// `char* s`: string
char* strreversecase(char* s);

#endif // STRUTILS_H