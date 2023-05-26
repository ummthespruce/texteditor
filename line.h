#pragma once
#include <stdio.h>
#include "types.h"


TLine init_line();
void free_line(TLine line);
void move_up(TLine line, char last);
void move_down(TLine line, char first);
void move_left(TLine line);
void move_right(TLine line);
void create_down(TLine line);
void create_on_cursor(TLine line, char value);
TDLListT delete_line_on_finger(TLine line);
void delete_character_on_cursor(TLine);
