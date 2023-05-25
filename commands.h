#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "stack.h"
#include "tape.h"
#include "types.h"

// undo redo functions
TUR init_ur();
void free_ur(TUR);
void empty_ur(TUR);

// update commands
void move_left_command(TTape, TUR);
void move_right_command(TTape, TUR);
void write_command(TTape, char, TUR);
void insert_left_command(TTape, char, FILE*);
void insert_right_command(TTape, char);
void move_left_char_command(TTape, char, FILE*);
void move_right_char_command(TTape, char);

// query commands
void show_current_command(TTape, FILE*);
void show_command(TTape, FILE*);

// undo redo comamnds
void undo_command(TTape, TUR);
void redo_command(TTape, TUR);

// execute command
void execute(TTape, TUR, TQueue, FILE*);
