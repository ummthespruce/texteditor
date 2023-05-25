#pragma once
#include <stdio.h>
#include "types.h"


TTape init_tape();
void free_tape(TTape);
TDLListT aloc_tape_cell(const TTYPE);