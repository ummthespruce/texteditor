#include <stdlib.h>
#include <stdio.h>
#include "tape.h"

// internal function
// this shouldnt be exported
inline static TDLListT aloc_cell(const TTYPE value) {
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
    temp->sentry = aloc_cell(0);
    temp->finger = temp->sentry;
    move_right(temp);
    return temp;
}

void free_tape(TTape tape) {
    // frees a tape
    free_list(&(tape->sentry));
    free(tape);
}

char create_left(TTape tape) {
    // creates an element to the left of the element, if it is not the first

    // returns 1 if the finger is on the first element
    // returns 0 and creates a new element on the left of the finger
    // otherwise
    // return value used later for checking if INSERT_LEFT is possible
    if (tape->finger->prev == tape->sentry)
        return 1;  // error, we cannot create an element before the first element
    TDLListT temp = aloc_cell('#');
    temp->next = tape->finger;
    temp->prev = tape->finger->prev;
    temp->prev->next = temp;
    tape->finger->prev = temp;
    return 0;
}

void create_right(TTape tape) {
    // creates an element to the right of the finger
    TDLListT temp = aloc_cell('#');
    temp->prev = tape->finger;
    temp->next = tape->finger->next;
    // the element the finger points at might not be the final element
    if (temp->next) {
        temp->next->prev = temp;
    }
    tape->finger->next = temp;
}

char move_left(TTape tape) {
    // moves the finger to the left, if it is not the first element
    // returns 1 if it is the first element
    // returns 0 if if is any other element and the move is possible
    if (tape->finger->prev == tape->sentry) {
        return 1;
    }
    tape->finger = tape->finger->prev;
    return 0;
}

void move_right(TTape tape) {
    // moves the finger to the right
    // and creates an element for it to move to
    // if it is the last element
    if (tape->finger->next == 0) {
        create_right(tape);
        tape->finger = tape->finger->next;
        return;
    }
    tape->finger = tape->finger->next;
}

void write(TTape tape, TTYPE value) {
    // writes a value to the element that is pointed by the finger
    tape->finger->value = value;
}

void print_tape(TTape tape, FILE* fp) {
    // prints the contents of a tape, with the current location
    // of the finger
    TDLListT aux = tape->sentry->next;
    for (; aux != tape->finger && aux; aux = aux->next) {
        fprintf(fp, "%c", aux->value);
    }
    fprintf(fp, "|%c|", aux->value);
    for (aux = aux->next; aux; aux = aux->next) {
        fprintf(fp, "%c", aux->value);
    }
    fprintf(fp, "\n");
}

// valgrind test for tape
// int main() {
//     TTape tape = init_tape();
//     print_tape(tape);
//     char test = create_left(tape);
//     if (test)
//         fprintf(OUTFILE, "impossible\n");
//     move_left(tape);
//     move_right(tape);
//     print_tape(tape);
//     write(tape,'c');
//     print_tape(tape);
//     create_left(tape);
//     create_right(tape);
//     print_tape(tape);
//     free_tape(tape);
// }


