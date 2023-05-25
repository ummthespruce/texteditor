#include "queue.h"

// internal function
// this shouldnt be exported
inline static TDLListQ aloc_cell(const QTYPE value) {
    // allocates a new cell for the double linked list
    TDLListQ temp = calloc(1, sizeof(struct dllq));
    temp->value = value;
    return temp;
}

// internal function
// this shouldnt be exported
inline static void add_cell_first(TDLListQ *list, const QTYPE value) {
    // adds a new cell at the beginning of the double linked list
    // and makes it the new head
    TDLListQ temp = aloc_cell(value);
    temp->next = *list;
    if (temp->next) {
        temp->next->prev = temp;
    }
    *list = temp;
}

// internal function
// this shouldnt be exported
inline static void free_cell(TDLListQ cell) {
    // frees a single cell
    free(cell);
    cell = 0;
}

// internal function
// this shouldnt be exported
inline static void free_list(TDLListQ *list) {
    // frees an entire double linked list
    TDLListQ aux = 0;
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
inline static void print_list(const TDLListQ list) {
    // debug function

    // prints the contents of a double linked list
    fprintf(OUTFILE, "[ ");
    TDLListQ aux = list;
    for (; aux; aux = aux->next) {
        fprintf(OUTFILE, "%X ", aux->value); /*hex value, 1 byte*/
    }
    fprintf(OUTFILE, "]\n");
}
#endif


TQueue init_queue() {
    // initializes a queue
    TQueue temp = calloc(1, sizeof(struct queue));
    return temp;
}

void free_queue(TQueue queue) {
    // frees a queue
    free_list(&(queue->head));
    free(queue);
}

void enqueue(TQueue queue, QTYPE value) {
    // enqueues an element

    // add a new head with our value
    add_cell_first(&(queue->head), value);
    // if the queue is empty, we make its ends point
    // to the same element
    if (queue->tail == 0) {
        queue->tail = queue->head;
    }
}

QTYPE dequeue(TQueue queue) {
    // if the queue isnt empty
    if (queue->tail) {
        QTYPE value = queue->tail->value;
        TDLListQ aux = queue->tail;
        queue->tail = queue->tail->prev;
        // if the queue has a single element
        // (the tail and the head are the same)
        if (aux == queue->head) {
            queue->head = 0;
        } else {
            queue->tail->next = 0;
        }
        free_cell(aux);
        return value;
    }
    // cannot return 0 for all data types
    // and it gives an error if i do not return
#if QTYPE == TCmd
    // // even if cpplint says i do not need a ; after this },
    // // the program would not compile afterwards as this is not
    // // a series of instructions, it is the cast of an object to a type
    // return (TCmd){0, 0};
    TCmd* wtf = calloc(1, sizeof(TCmd));
    TCmd value = *wtf;
    free(wtf);
    return value;

#else
    return 0;
#endif
#ifdef debug
    fprintf(OUTFILE, "ERROR: cannot dequeue from empty queue\n");
#endif
}

#ifdef debug
void print_queue(TQueue queue) {
    // debug function, prints the queue
    print_list(queue->head);
}
#endif

// // valgrind test for queue
// int main() {
//     TQueue queue = init_queue();
//     enqueue(queue, 5);
//     fprintf(OUTFILE, "test\n");
//     enqueue(queue, 7);
//     enqueue(queue, 6);
//     print_queue(queue);
//     char c = 0;
//     c = dequeue(queue);
//     fprintf(OUTFILE, "%d\n", c);
//     print_queue(queue);
//     c = dequeue(queue);
//     fprintf(OUTFILE, "%d\n", c);
//     print_queue(queue);
//     c = dequeue(queue);
//     fprintf(OUTFILE, "%d\n", c);
//     print_queue(queue);
//     c = dequeue(queue);
//     fprintf(OUTFILE, "%d\n", c);
//     print_queue(queue);
//     enqueue(queue, 1);
//     c = dequeue(queue);
//     fprintf(OUTFILE, "%d\n", c);
//     print_queue(queue);
//     free_queue(queue);
// }
