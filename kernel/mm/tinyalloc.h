#ifndef TINYALLOC_H
#define TINYALLOC_H

#include <stdbool.h>
#include "../include/libc/string.h"

bool ta_init(const void *base, const void *limit, const size_t heap_blocks, const size_t split_thresh, const size_t alignment);
void *malloc(size_t num);
void *calloc(size_t num, size_t size);
bool free(void *ptr);
void* realloc(void* Block, size_t size);

size_t ta_num_free();
size_t ta_num_used();
size_t ta_num_fresh();
bool ta_check();

#endif
