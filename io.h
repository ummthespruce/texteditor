#pragma once

#include "types.h"
#include "line.h"
#include "tape.h"
#include <stdio.h>


char add_buffer_to_tape(char *, TDLListT *);
TLine readfile(const char *);
void writefile(const char *, TLine);
