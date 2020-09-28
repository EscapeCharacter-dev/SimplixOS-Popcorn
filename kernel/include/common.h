#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <stddef.h>
#include "libc/cdefs.h"

int ______KPANIC______;

#define ______KPANIC_UNKNOWN_ARCH 0xFFFFFFFF

/* at least 8-bit */
typedef signed char        int8_t;
typedef unsigned char      uint8_t;

/* at least 16-bit */
typedef short              int16_t;
typedef unsigned short     uint16_t;

/* at least 32-bit */
typedef long               int32_t;
typedef unsigned long      uint32_t;

/* at least 64-bit */
typedef long long          int64_t;
typedef unsigned long long uint64_t;

/* Custom modifier */
#define interrupt __attribute__((interrupt))

#if defined __i386__        // 32-bit
typedef long               word;
typedef unsigned long      uword;
#elif defined __x86_64__    // 64-bit
typedef long long          word;
typedef unsigned long long uword;
#else                       // OK WHAT IS GOING ON?!!!
typedef signed char        word;
typedef unsigned char      uword;
______KPANIC______ = ______KPANIC_UNKNOWN_ARCH;
#endif

#define ERRNO_EOVERFLOW   -2
#define ERRNO_NOTLEGALINT -3
#define ERRNO_FAILEDPTR   -4

int errno;

enum __VGA_COLOR__T
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    GREY,
    DARK_GREY,
    BRIGHT_BLUE,
    BRIGHT_GREEN,
    BRIGHT_CYAN,
    BRIGHT_RED,
    BRIGHT_MAGENTA,
    YELLOW,
    WHITE
};

/* functions */

extern uint8_t g_fore_color;
extern uint8_t g_back_color;

extern int tab_length;

void changecolor(uint8_t fore, uint8_t back);
uint16_t vga_entry(uint8_t ch, uint8_t fore, uint8_t back);
void clear_vga_buffer(uint16_t **buffer, uint8_t fore, uint8_t back);
void init_vga(uint8_t fore, uint8_t back);
void print_new_line();
void printkch(char ch);
//uint32_t strlen(const char *str);
uint32_t digit_count(int num);
void itoa(int num, char *number);
void printk(char *str);
void printki(int num);
char getInput();
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void disable_cursor();
void update_cursor(int x, int y);
void update_cursor_to_index();

#endif