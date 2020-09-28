#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

#include "../include/common.h"

typedef struct interrupt_frame_t
{
    uword ip;
    uword cs;
    uword flags;
    uword sp;
    uword ss;
} interrupt_frame;

interrupt void interrupt_handler(interrupt_frame *frame);

#endif