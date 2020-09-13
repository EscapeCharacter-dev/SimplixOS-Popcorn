#include "./string.h"

void *memcpy(void *restrict dstptr, const void *restrict srcptr, size_t size)
{
    uint8_t *dst = (uint8_t*) dstptr;

    const uint8_t *src = (uint8_t*) srcptr;

    for (size_t i = 0; i < size; i++)
        dst[i] = src[i];

    return dstptr;
}