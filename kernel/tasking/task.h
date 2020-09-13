#ifndef TASK_H
#define TASK_H

#include "../include/common.h"

typedef struct Process_t
{

    uint8_t *code;    /* Code is public */
    void    *data;    /* Data is public */
    void    *heap;    /* Heap is public */
    void    *stack;   /* Public stack */
    Thread  *threads; /* Sub-threads */
    Thread  *flow;    /* Main thread, talking to system mostly. */

} Process;

typedef struct Thread_t
{

    void    *stack;  /* Thread stack */

} Thread;

#endif