#ifndef ATA_DRIVER_H
#define ATA_DRIVER_H

#include "../../include/krnlutils.h"

void read_sectors_ATA_PIO(uint32_t target_address, uint32_t lba, uint8_t sector_count);
void write_sectors_ATA_PIO(uint32_t lba, uint8_t sector_count, uint32_t *source);

#endif
