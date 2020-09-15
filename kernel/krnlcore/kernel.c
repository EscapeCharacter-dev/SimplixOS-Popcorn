#include "../include/common.h"
#include "../mm/tinyalloc.h"
#include "../kdrivers/ata/ata.h"
#include "../include/libc/stdio.h"
#include "../kdrivers/fs/isocd.h"
#include "../vga/vga_driver.h"

#include "../real/v8086.h"

void kernel_ep(void)
{
    uint32_t *screen = (uint32_t*) 0xA0000;

    int color;
    toRGB(&color, 68, 177, 255);

    fillrectangle(screen, 0xFF0000, 20, 20);

    while(1)
    {
        
        /*char c = getInput();

        printkch(c);*/
    }
}
