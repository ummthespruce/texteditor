#include "stack.h"

// internal function
// this shouldnt be exported
inline static TLListS aloc_cell(const STYPE value) {
    // allocates a new cell for the linked list
    TLListS temp = calloc(1, sizeof(struct lls));
    temp->value = value;
    return temp;
}

// internal function
// this shouldnt be exported
inline static void add_cell_first(TLListS *list, const STYPE value) {
    // adds a new cell at the beginning of the linked list
    // and makes it the new head
    TLListS temp = aloc_cell(value);
    temp->next = *list;
    *list = temp;
}

// internal function
// this shouldnt be exported
inline static void free_cell(TLListS cell) {
    // frees a single cell
    free(cell);
    cell = 0;
}

// internal function
// this shouldnt be exported
inline static void free_list(TLListS *list) {
    // frees an entire linked list
    TLListS aux = 0;
    for (; *list; ) {
        aux = *list;
        *list = aux->next;
        free_cell(aux);
    }
    *list = 0;
}

// internal function
// this shouldnt be exported
#ifdef debug
inline static void print_list(const TLListS list) {
    // debug function
    // prints the contents of a linked list
    fprintf(stdout, "[ ");
    TLListS aux = list;
    for (; aux; aux = aux->next) {
        fprintf(stdout, "%p ", aux->value);  // hex value, 1 byte
    }
    fprintf(stdout, "]\n");
}
#endif


TStack init_stack() {
    // initializes a stack
    TStack temp = calloc(1, sizeof(struct stack));
    return temp;
}

TStack free_stack(TStack stack) {
    // frees a stack
    free_list(&(stack->head));
    free(stack);
    return 0;
}

void push(TStack stack, STYPE value) {
    // pushes an element onto the stack
    add_cell_first(&(stack->head), value);
}

STYPE pop(TStack stack) {
    // pops an element from the stack
    if (stack->head) {
        STYPE value = stack->head->value;
        TLListS aux = stack->head;
        stack->head = stack->head->next;
        free_cell(aux);
        return value;
    }
#ifdef debug
    fprintf(OUTFILE, "ERROR: trying to pop stack when stack is empty\n");
#endif
    return 0;
}

void empty_stack(TStack stack) {
    // empties the stack
    free_list(&(stack->head));
    stack = 0;
}

#ifdef debug
void print_stack(TStack stack) {
    // debug function, prints the stack
    print_list(stack->head);
}
#endif


// // valgrind test for stack
// int main() {
//     TStack stack = init_stack();
//     push(stack, 5);
//     push(stack, 7);
//     push(stack, 6);
//     print_stack(stack);
//     char c = 0;
//     c = pop(stack);
//     fprintf(OUTFILE, "%d\n", c);
//     print_stack(stack);
//     c = pop(stack);
//     fprintf(OUTFILE, "%d\n", c);
//     print_stack(stack);
//     c = pop(stack);
//     fprintf(OUTFILE, "%d\n", c);
//     print_stack(stack);
//     c = pop(stack);
//     fprintf(OUTFILE, "%d\n", c);
//     print_stack(stack);
//     push(stack, 1);
//     c = pop(stack);
//     fprintf(OUTFILE, "%d\n", c);
//     print_stack(stack);
//     empty_stack(stack);
//     push(stack,1);
//     free_stack(stack);
// }
