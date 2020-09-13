#include <limits.h>
#include <stdarg.h>
#include "../common.h"
#include "./stdio.h"
#include "./string.h"

static int print(const char *data, size_t length)
{
    const uint8_t *bytes = (const uint8_t*) data;
    for (size_t i = 0; i < length; i++)
        if (putchar(bytes[i]) == EOF)
            return 0;
    return 1;
}

static int fprint(const char *data, size_t length, int *FHANDLE)
{
    const uint8_t *bytes = (const uint8_t*) data;
    for (size_t i = 0; i < length; i++)
        if (fputchar(bytes[i], FHANDLE) == EOF)
            return 0;
    return 1;
}

int printf(const char *restrict format, ...)
{
    va_list parameters;
    va_start(parameters, format);

    int written = 0;

    while (*format != '\0')
    {
        size_t maxrem = INT_MAX - written;

        if (format[0] != '%' || format[1] == '%')
        {
            if (format[0] == '%')
                format++;

            size_t amount = 1;
            while(format[amount] && format[amount] != '%')
                amount++;

            if (maxrem < amount)
            {
                errno = ERRNO_EOVERFLOW;
                return -1;
            }

            if (!print(format, amount))
                return -1;
            format += amount;
            written += amount;
            continue;
        }

        const int8_t* format_begun_at = format++;

        if (*format == 'c') {
			format++;
			int8_t c = (char) va_arg(parameters, int);
			if (!maxrem) {
				errno = ERRNO_EOVERFLOW;
				return -1;
			}
			if (!print(&c, sizeof(c)))
				return -1;
			written++;
		} else if (*format == 's') {
			format++;
			const int8_t* str = va_arg(parameters, const int8_t*);
			size_t len = strlen(str);
			if (maxrem < len) {
				errno = ERRNO_EOVERFLOW;
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
		} else {
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len) {
				errno = ERRNO_EOVERFLOW;
				return -1;
			}
			if (!print(format, len))
				return -1;
			written += len;
			format += len;
		}
    }
    return written;
}

int fprintf(const char *restrict format, int *FHANDLE, ...)
{
    va_list parameters;
    va_start(parameters, format);

    int written = 0;

    while (*format != '\0')
    {
        size_t maxrem = INT_MAX - written;

        if (format[0] != '%' || format[1] == '%')
        {
            if (format[0] == '%')
                format++;

            size_t amount = 1;
            while(format[amount] && format[amount] != '%')
                amount++;

            if (maxrem < amount)
            {
                errno = ERRNO_EOVERFLOW;
                return -1;
            }

            if (!fprint(format, amount, FHANDLE))
                return -1;
            format += amount;
            written += amount;
            continue;
        }

        const int8_t* format_begun_at = format++;

        if (*format == 'c') {
			format++;
			int8_t c = (char) va_arg(parameters, int);
			if (!maxrem) {
				errno = ERRNO_EOVERFLOW;
				return -1;
			}
			if (!fprint(&c, sizeof(c), FHANDLE))
				return -1;
			written++;
		} else if (*format == 's') {
			format++;
			const int8_t* str = va_arg(parameters, const int8_t*);
			size_t len = strlen(str);
			if (maxrem < len) {
				errno = ERRNO_EOVERFLOW;
				return -1;
			}
			if (!fprint(str, len, FHANDLE))
				return -1;
			written += len;
		} else {
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len) {
				errno = ERRNO_EOVERFLOW;
				return -1;
			}
			if (!fprint(format, len, FHANDLE))
				return -1;
			written += len;
			format += len;
		}
    }
    return written;
}

/*
 *
 * Here you got an example of why you should learn hacking for low-level developement.
 * You might now that I'm really bad at finding safe solutions, so all code starting
 * with f (for file) here is REALLY UNSAFE and is still temporary. A hacker would be probably
 * able to fix it, but because I prefer to spend my time learning computer science,
 * I don't have these useful skills.
 * 
 *      - EscapeCharacter, 2020/08/09 (2020/09/08 if you are not in U.S.)
 * 
*/

int findex = 0;

int fgetch(int *FHANDLE)
{
    return *(FHANDLE + ++findex);
}

#include "../../mm/tinyalloc.h"

int fgetstr(int *FHANDLE, size_t count, const char* buffer)
{
    int *charactersbuf = (int*) malloc(sizeof(int));

    int position;

    if (count <= 0)
    {
        errno = ERRNO_NOTLEGALINT;
        return 0;
    }

    for (int i = 0; i < count; i++)
    {
        if (charactersbuf != sizeof(int)) /* memory optimization */
            charactersbuf = (int*) malloc(sizeof(charactersbuf) + sizeof(int));

        charactersbuf[position++] = fgetch(FHANDLE);
    }

    if(!memcpy(buffer, charactersbuf, sizeof(charactersbuf)))
    {
        errno = ERRNO_FAILEDPTR;
        return 0;
    }

    return 1;
}