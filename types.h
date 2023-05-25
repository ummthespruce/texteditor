#pragma once

#define QTYPE TCmd
#define TTYPE char
#define STYPE TDLListT

#define INFILE "tema1.in"
#define OUTFILE "tema1.out"

// #define debug
// only used for encoding the update commands
enum Commands{
    UNDEFINED,
    MOVE_LEFT,
    MOVE_RIGHT,
    SHOW_CURRENT,
    SHOW,
    UNDO,
    REDO,
    EXECUTE,
    // the ones below have an argument
    MOVE_LEFT_CHAR,
    MOVE_RIGHT_CHAR,
    WRITE,
    INSERT_LEFT,
    INSERT_RIGHT
};

typedef struct cmd {
    enum Commands command;
    char arg1;
}TCmd;

typedef struct dllq {
    struct dllq *prev, *next;
    QTYPE value;
} *TDLListQ, TDLCellQ;

typedef struct queue {
    TDLListQ head;
    TDLListQ tail;
} *TQueue;




typedef struct dllt {
    struct dllt *prev, *next;
    TTYPE value;
} *TDLListT, TDLCellT;

typedef struct tape {
    TDLListT sentry;
    TDLListT finger;
} *TTape;



typedef struct lls {
    struct lls *next;
    STYPE value;
} *TLListS, TLCellS;

typedef struct stack {
    TLListS head;
}*TStack;


// used for holding both the undo and redo stacks
// in the same place
typedef struct undoredo {
    TStack undo;
    TStack redo;
}*TUR;




