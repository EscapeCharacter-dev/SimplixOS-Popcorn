#include "ata.h"

#define ATA_STATUS_BSY 0x80
#define ATA_STATUS_BSY 0x40
#define ATA_STATUS_DRQ 0x08
#define ATA_STATUS_DF  0x20
#define ATA_STATUS_ERR 0x01

static void ATA_wait_BSY();
static void ATA_wait_DRQ();

void read_sectors_ATA_PIO(uint32_t target_address, uint32_t lba, uint8_t sector_count)
{
    ATA_wait_BSY();
    outb(0x1F6, 0xE0 | ((lba >> 24) & 0xF));
    outb(0x1F2, sector_count);
    outb(0x1F3, (uint8_t) lba);
    outb(0x1F4, (uint8_t)(lba >> 8));
    outb(0x1F5, (uint8_t)(lba >> 16));
    outb(0x1F7, 0x20);

    uint16_t *target = target_address;

    for (int j = 0; j < sector_count; j++)
    {
        ATA_wait_BSY();
        ATA_wait_DRQ();

        for (int i = 0; i < 256; i++)
            target[i] = inb(0x1F0);
        target += 256;
    }
}

void write_sectors_ATA_PIO(uint32_t lba, uint8_t sector_count, uint32_t *source)
{
    ATA_wait_BSY();
    outb(0x1F6, 0xE0 | ((lba >> 24) & 0xF));
	outb(0x1F2, sector_count);
	outb(0x1F3, (uint8_t)lba);
	outb(0x1F4, (uint8_t)(lba >> 8));
	outb(0x1F5, (uint8_t)(lba >> 16));
	outb(0x1F7, 0x30);

    for (int j = 0; j < sector_count; j++)
    {
        ATA_wait_BSY();
        ATA_wait_DRQ();

        for (int i = 0; i < 256; i++)
        {
            outl(0x1F0, source[i]);
        }
    }
}

static void ATA_wait_BSY()
{
    while (inb(0x1F7) & ATA_STATUS_BSY);
}

static void ATA_wait_DRQ()
{
    while(!(inb(0x1F7) & ATA_STATUS_DRQ));
}