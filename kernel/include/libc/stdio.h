#ifndef _STDIO_H
#define _STDIO_H

#include "../common.h"

#define EOF (-1)

int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);
int fputchar(int ic, int *FHANDLE);
int fprintf(const char *restrict format, int *FHANDLE, ...);
int fscanf(const char *restrict format, int *FHANDLE, ...); /* TODO: IMPLEMENT */
int fgetch(int *FHANDLE);
int fgetstr(int *FHANDLE, size_t count, const char* buffer);

#endif