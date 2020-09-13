#include "./stdio.h"

int putchar(int ic)
{
    char c = (char) ic;

    printkch(c);
    return ic;
}

int fputchar(int ic, int *FHANDLE)
{
    char c = (char) ic;

    *FHANDLE++;
    *FHANDLE = c;
    return ic;
}