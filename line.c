#include <stdlib.h>
#include <stdio.h>
#include "line.h"
#include "tape.h"
// internal function
// this shouldnt be exported
inline static TDLListL aloc_cell() {
    // allocates a new cell for the double linked list
    TDLListL temp = calloc(1, sizeof(struct dlll));
    temp->value = init_tape();
    return temp;
}

// internal function
// this shouldnt be exported
inline static void free_cell(TDLListL cell) {
    // frees a single cell
	free_tape(cell->value);
    free(cell);
    cell = 0;
}

// internal function
// this shouldnt be exported
inline static void free_list(TDLListL *list) {
    // frees an entire double linked list
    TDLListL aux = 0;
    for (; *list; ) {
        aux = *list;
        *list = aux->next;
        free_cell(aux);
    }
    *list = 0;
}

TLine init_line() {
    // initializes a line
    TLine temp = calloc(1, sizeof(struct line));
	temp->sentry = aloc_cell();
	temp->finger = temp->sentry;
	create_down(temp);
	temp->finger = temp->sentry->next;
	temp->cursor = temp->finger->value->next;
	
	// create_on_cursor
	temp->posx = 1;
	temp->posy = 1;
	int posline = 1;
    return temp;
}

void free_line(TLine line) {
    // frees a line
    free_list(&(line->sentry));
    free(line);
}


void move_up(TLine line, char last) {
	// if we can move up, do so
    if (line->finger->prev != line->sentry) {
		line->finger = line->finger->prev;
		int x = 1;
		int xmax = line->posline;
		line->posy--;
		TDLListT temp = line->finger->value;
		// go right as much as we can until we arrive at posline or at last value
		if (!last) {
			for (; temp && x < xmax ; x++, temp = temp->next);
		} else { // called when moving left from first position
			for (; temp; x++, temp = temp->next);
			line->posline = x; 
		}
		line->posx = x;
		line->cursor = temp;
    } else { // if we are on the first line, move to first position
		line->posx = 1;
		line->cursor = line->finger->value;
	}
    return 0;
}

void move_down(TLine line, char first) {
	// if we can move down, do so
    if (line->finger->next != 0) {
        // go right as much as we can until we arrive at
		// posline or at last value
		line->finger = line->finger->next;
		int x = 1;
		int xmax = line->posline;
		line->posy++;
		TDLListT temp = line->finger->value;
		if (!first) {
			for (; temp && x < xmax ; x++, temp = temp->next);
		} else { // called when moving right from last position
			line->posline = x;
		}
		line->posx = x;
        line->cursor = temp;
	} else { // we are on the last line, move to last position
		int x = 1;
		TDLListT temp = line->finger->value;
		for (; temp; x++, temp = temp->next);
		line->posx = x;
		line->cursor = temp;
	}
}

void move_left(TLine line) {
	// if next element is not the first, move left
    if (line->cursor->prev != line->finger->value->sentry) {
		line->posx--;
		line->posline = line->posx;
		line->cursor = line->cursor->prev;
    } else { // otherwise, move up by 1 to the last position
		move_up(line, 1);
 	}
}

void move_right(TLine line) {
	// if the next element is not the last, move right
    if (line->cursor->next != 0) {
		line->posx++;
		line->posline = line->posx;
		line->cursor = line->cursor->next;
    } else { // if we are on the last element of the line
		move_down(line, 1);
	}
}

void create_down(TLine line) {
    // creates a new line below
    TDLListL temp = aloc_cell();
    temp->prev = line->finger;
    temp->next = line->finger->next;
    // the element the finger points at might not be the final element
    if (temp->next) {
        temp->next->prev = temp;
    }
    line->finger->next = temp;
}

void create_on_cursor(TLine line, char value) {
    // creates an element to the right of the cursor
    TDLListT temp = aloc_tape_cell(value);
    temp->prev = line->cursor;
    temp->next = line->cursor->next;
    // the element the finger points at might not be the final element
    if (temp->next) {
        temp->next->prev = temp;
    }
    line->cursor->next = temp;
}

