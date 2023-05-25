#pragma once
#include <stdio.h>
#include "types.h"


TTape init_tape();
void free_tape(TTape);
char create_left(TTape);
void create_right(TTape);
char move_left(TTape);
void move_right(TTape);
void write(TTape, TTYPE);
void print_tape(TTape, FILE*);
