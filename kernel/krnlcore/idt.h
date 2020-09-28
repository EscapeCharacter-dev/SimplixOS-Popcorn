#include "../include/common.h"

struct IDTDescriptor_32_t
{

    uint16_t offset_1;
    uint16_t selector;
    uint8_t  zero;
    uint8_t  type_attribute;
    uint16_t offset_2;

} IDTDescriptor_32;

struct IDTDescriptor_64_t
{

    uint16_t offset_1;
    uint16_t selector;
    uint8_t  ist;
    uint8_t  type_attribute;
    uint16_t offset2;
    uint32_t offset3;
    uint32_t zero;

} IDTDescriptor_64;