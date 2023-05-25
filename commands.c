#include "commands.h"
// initialize the undo redo stacks
TUR init_ur() {
    TUR ur = calloc(1, sizeof(struct undoredo));
    ur->undo = calloc(1, sizeof(struct stack));
    ur->redo = calloc(1, sizeof(struct stack));
    return ur;
}

// free the undo redo stacks
void free_ur(TUR ur) {
    free_stack(ur->undo);
    free_stack(ur->redo);
    free(ur);
}

// empty all of the undo redo stacks
void empty_ur(TUR ur) {
    empty_stack(ur->undo);
    empty_stack(ur->redo);
}

// function for the MOVE_LEFT command
void move_left_command(TTape tape, TUR ur) {
    char check = move_left(tape);
    // if it can move to the left, push onto the
    // undo stack the current position
    if (!check) {
        push(ur->undo, tape->finger->next);
    }
}

// function for the MOVE_RIGHT command
void move_right_command(TTape tape, TUR ur) {
    // it can always move to the right, so
    // push onto the undo stack the current position
    push(ur->undo, tape->finger);
    move_right(tape);
}

// function for the WRITE command
// DIFFERENT FROM THE write FUNCTION
void write_command(TTape tape, char C, TUR ur) {
    write(tape, C);
    // empty the undo redo stacks as the problem calls for it
    empty_ur(ur);
}

// function for the INSERT_LEFT command
void insert_left_command(TTape tape, char C, FILE* fp) {
    // if it cannot create a cell on the left, print an error
    char check = create_left(tape);
    if (check) {
        fprintf(fp, "ERROR\n");
        return;
    }
    // if the create left function succeded, move left and
    // write the character C
    move_left(tape);
    write(tape, C);
}

// function for the INSERT_RIGHT command
void insert_right_command(TTape tape, char C) {
    // we can always move to the right, so create a cell on the right,
    // move right and write the character C
    create_right(tape);
    move_right(tape);
    write(tape, C);
}

// function for the MOVE_LEFT_CHAR command
void move_left_char_command(TTape tape, char C, FILE* fp) {
    TDLListT aux = tape->finger;
    // start the sewritearch for the element containing C, starting from
    // the finger and going to the beginning
    for (; aux->value != C && aux->prev != tape->sentry; aux = aux->prev) {}
    // if it is found, move the finger to the element
    if (aux->value == C) {
        tape->finger = aux;
        return;
    }
    // if it is not found, print an error
    fprintf(fp, "ERROR\n");
}

// function for the MOVE_RIGHT_CHAR command
void move_right_char_command(TTape tape, char C) {
    // start the search for the element containing C, starting from
    // the finger and going to the end
    TDLListT aux = tape->finger;
    for (; aux->value != C && aux->next; aux = aux->next) {}
    // move the finger to the element, which is either an element
    // containing C or the end
    tape->finger = aux;
    // if the element contains C, return
    if (aux->value == C) {
        return;
    }
    // else, move right once, as we are at the end and we
    // have any element containing C
    move_right(tape);
}

// function for the SHOW_CURRENT command
void show_current_command(TTape tape, FILE* fp) {
    // prints the character contained in the element
    // the finger currently points at
    fprintf(fp, "%c\n", tape->finger->value);
}

// function for the SHOW command
inline void show_command(TTape tape, FILE* fp) {
    // prints the contents of the tape
    print_tape(tape, fp);
}

// function for the UNDO command
void undo_command(TTape tape, TUR ur) {
    // takes the previously pointed at from the
    // undo stack, pushes the current position onto the
    // redo stack and moves the finger to the previous position
    STYPE aux = pop(ur->undo);
    push(ur->redo, tape->finger);
    tape->finger = aux;
}

// function for the REDO command
void redo_command(TTape tape, TUR ur) {
    // takes the previously pointed at from the
    // redo stack, pushes the current position onto the
    // undo stack and moves the finger to the previous position
    STYPE aux = pop(ur->redo);
    push(ur->undo, tape->finger);
    tape->finger = aux;
}

// function for the EXECUTE command
void execute(TTape tape, TUR ur, TQueue queue, FILE* fp) {
    // extracts a command from the queue
    QTYPE cmd = dequeue(queue);
    // based on the command code, execute it
    switch (cmd.command) {
        case MOVE_LEFT:
            move_left_command(tape, ur);
            break;
        case MOVE_RIGHT:
            move_right_command(tape, ur);
            break;
        case MOVE_LEFT_CHAR:
            move_left_char_command(tape, cmd.arg1, fp);
            break;
        case MOVE_RIGHT_CHAR:
            move_right_char_command(tape, cmd.arg1);
            break;
        case WRITE:
            write_command(tape, cmd.arg1, ur);
            break;
        case INSERT_LEFT:
            insert_left_command(tape, cmd.arg1, fp);
            break;
        case INSERT_RIGHT:
            insert_right_command(tape, cmd.arg1);
            break;
        // in case it is undefined or something else, print out an error
        case UNDEFINED:
        default:
            fprintf(fp, "ERROR IN EXECUTE, NO COMMAND MATCHED\n");
    }
}
