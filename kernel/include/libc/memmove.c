#include "./string.h"

void *memmove(void *dst, const void *source, size_t size)
{
    uint8_t *destination = (uint8_t*) dst;

    const uint8_t *src = (const uint8_t*) source;

    if (destination < src)
    {
        for (size_t i = 0; i < size; i++)
            destination[i] = src[i];
    }
    else
    {
        for (size_t i = size; i != 0; i--)
            destination[i - 1] = src[i - 1];
    }

    return dst;
}