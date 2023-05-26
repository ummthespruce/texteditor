#pragma once

#include <curses.h>
#include "types.h"

#define MAXFILENAMESIZE 30
#define MAXLINENUMBERSIZE 4
#define MAXFILENAMELINES 2
#define MAXSTATELINES 2

void init_FW(OpenedFileT);
void update(OpenedFileT);
void remove_window_info(OpenedFileT);