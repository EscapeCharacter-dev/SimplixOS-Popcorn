#include "../include/common.h"
#include "../mm/tinyalloc.h"
#include "../kdrivers/ata/ata.h"
#include "../include/libc/stdio.h"
#include "../kdrivers/fs/fat.h"

void kernel_ep(void)
{
    init_vga(GREY, BLACK);

    printk("Starting reading disk... ~~~ Format = FAT32\n");

    int HANDLE = fat_open("sys/sntychk", O_RDONLY);

    init_fat();

    int size = fat_fsize(HANDLE);

    const char *buffer = (const char*) malloc(sizeof(size));

    if(!fgetstr(HANDLE, size, buffer))
    {
        switch (errno)
        {
            case ERRNO_EOVERFLOW:
                printk("Overflow\n");
                break;
            case ERRNO_NOTLEGALINT:
                printk("\"Illegal\" integer value\n");
                break;
            case ERRNO_FAILEDPTR:
                printk("Buffer overflow\n");
                break;
        }
    }
    else
    {
        printk(buffer);
    }

    fat_close(HANDLE);

    while(1)
    {
        char c = getInput();

        printkch(c);
    }
}
