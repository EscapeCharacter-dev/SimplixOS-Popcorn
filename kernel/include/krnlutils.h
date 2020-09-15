#ifndef KRNLUTILS_H
#define KRNLUTILS_H

#include "common.h"

void outb(uint16_t port, uint8_t data);
void outs(uint16_t port, uint16_t data);
void outl(uint16_t port, uint32_t data);
void outw(uint16_t port, int data);

uint8_t inb(uint16_t port);
uint16_t ins(uint16_t port);
uint32_t inl(uint16_t port);
int inw(uint16_t port);

int eax();
int ebx();
int ecx();
int edx();
int esp();
int eip();
int cs();

void nop();

#endif
