#ifndef _STRING_H
#define _STRING_H

#include "../common.h"

int memcmp(const void*, const void*, size_t);
void *memcpy(void*restrict, const void*restrict, size_t);
void *memmove(void*, const void*, size_t);
void *memset(void*, int, size_t);
size_t strlen(const char *str);
char *strtok(char *str, const char *delemiters);

#endif