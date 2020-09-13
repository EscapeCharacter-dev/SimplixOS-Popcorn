#include "../include/common.h"

void outb(uint16_t port, uint8_t data)
{
    asm volatile("outb %0, %1" : "=a"(data) : "d"(port));
}

void outl(uint16_t port, uint32_t data)
{
    asm volatile("outl %0, %1" : "=a"(data) : "d"(port));
}

void outw(uint16_t port, int data)
{
    asm volatile("outw %0, %1" : "=a"(data) : "d"(port));
}

uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
    return ret;
}

uint32_t inl(uint16_t port)
{
    uint32_t ret;
    asm volatile("inl %1, %0" : "=a"(ret) : "d"(port));
    return ret;
}

int inw(uint16_t port)
{
    int ret;
    asm volatile("inw %1, %0" : "=a"(ret) : "d"(port));
    return ret;
}

void nop()
{
    asm volatile("nop");
}