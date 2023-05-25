#include <stdlib.h>
#include <stdio.h>
#include "tape.h"


TDLListT aloc_tape_cell(const TTYPE value) {
    // allocates a new cell for the double linked list
    TDLListT temp = calloc(1, sizeof(struct dllt));
    temp->value = value; 
    return temp;
}

// internal function
// this shouldnt be exported
inline static void free_cell(TDLListT cell) {
    // frees a single cell
    free(cell);
    cell = 0;
}

// internal function
// this shouldnt be exported
inline static void free_list(TDLListT *list) {
    // frees an entire double linked list
    TDLListT aux = 0;
    for (; *list; ) {
        aux = *list;
        *list = aux->next;
        free_cell(aux);
    }
    *list = 0;
}

TTape init_tape() {
    // initializes a tape
    TTape temp = calloc(1, sizeof(struct tape));
    temp->sentry = aloc_tape_cell(0);
    return temp;
}

void free_tape(TTape tape) {
    // frees a tape
    free_list(&(tape->sentry));
    free(tape);
}

