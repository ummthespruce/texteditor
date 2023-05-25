#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "types.h"
TStack init_stack();
TStack free_stack(TStack);
void push(TStack, STYPE);
STYPE pop(TStack);
void empty_stack(TStack);
#ifdef debug
void print_stack(TStack);
#endif
