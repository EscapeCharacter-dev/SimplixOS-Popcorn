#include "./string.h"

size_t strlen(const char *str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

#include "./stdio.h"

char *sp = 0;

char *strtok(char *str, const char *delimiters)
{
    int i = 0;
    int len = strlen(delimiters);

    if (len == 0)
        printf("Delimiters are empty\n");

    if (!str && !sp)
        return 0;

    if (str && !sp)
        return 0;

    char *p_start = sp;

    while (1)
    {
        for (i = 0; i < len; i++)
        {
            if (*p_start == delimiters[i])
            {
                p_start++;
                break;
            }
        }

        if (i == len)
        {
            sp = p_start;
            break;
        }
    }

    if (*sp == '\0')
    {
        sp = 0;
        return sp;
    }

    while (*sp != '\0')
    {
        for (i = 0; i < len; i++)
        {
            if (*sp == delimiters[i])
            {
                *sp = '\0';
                break;
            }
        }

        sp++;

        if (i < len)
            break;
    }

    return p_start;
}