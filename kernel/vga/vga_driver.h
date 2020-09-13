#ifndef STANDART_VGA_DRIVER_H
#define STANDART_VGA_DRIVER_H

#include "../include/common.h"

void putpixel(unsigned char *screen, int x, int y, int color);
void fillrectangle(unsigned char *vram, int color, uint8_t w, uint8_t h);
void getRGB(int color, uint8_t *r, uint8_t *g, uint8_t *b);
void toRGB(int *color, uint8_t r, uint8_t g, uint8_t b);

#endif
