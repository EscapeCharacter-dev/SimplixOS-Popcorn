#include "vga_driver.h"

void getRGB(int color, uint8_t *r, uint8_t *g, uint8_t *b)
{
    *r = color & 255;
    *g = (color >> 8) & 255;
    *b = (color >> 16) & 255;
}

void toRGB(int *color, uint8_t r, uint8_t g, uint8_t b)
{
    *color = (r << 16) | (g << 8) | b;
}

void putpixel(unsigned char *screen, int x, int y, int color)
{
    unsigned int where = x + y;

    screen[where] = color & 255;
    screen[where + 1] = (color >> 8) & 255;
    screen[where + 2] = (color >> 16) & 255;
}

void fillrectangle(unsigned char *vram, int color, uint8_t w, uint8_t h)
{
    uint8_t *where = vram;

    uint8_t r, g, b;

    getRGB(color, &r, &g, &b);

    for (int i = 0; i < w; i++)
    {
        for (int j = h; j >= 0; j--)
        {
            /*putpixel(vram, 64 + j, 64 + i, (r << 16) + (g << 8) + b);*/
            where[j * 4] = r;
            where[j * 4 + 1] = g;
            where[j * 4 + 2] = b;
        }
        where += 1;
    }
}