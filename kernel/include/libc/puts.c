#include "./stdio.h"

int puts(const char *string)
{
    return printf("%s\n", string);
}

int fputs(const char *string, int FHANDLE)
{
    return fprintf("%s\n", string);
}