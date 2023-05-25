#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "types.h"

TQueue init_queue();
void free_queue(TQueue);
void enqueue(TQueue, QTYPE);
QTYPE dequeue(TQueue);
#ifdef debug
void print_queue(TQueue);
#endif
