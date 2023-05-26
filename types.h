#pragma once
#include <curses.h>

#define QTYPE TCmd
#define TTYPE char
#define STYPE TDLListT
#define LTYPE TTape

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

enum States {
	NONE,
	INSERT
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
} *TTape;


typedef struct dlll {
    struct dlll *prev, *next;
    LTYPE value;
} *TDLListL, TDLCellL;

typedef struct line {
	// for lines
    TDLListL sentry;
	
	// for line finger
	TDLListL finger;
	
	// for cursor
    TDLListT cursor;
	TDLListL linepos;
	// for the current position
	int posx;
	int posy;
	
	// for the position where it should be after going down or up
	int posline;
} *TLine;


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

typedef struct filewindow {
	WINDOW *filewin;
	WINDOW *linewin;
	WINDOW *contentwin;	
	WINDOW *statewin;
	int yMax, xMax;
	int yBeg, xBeg;
} FileWindowT;

typedef struct openfile {
	FileWindowT FW;
	char *filename;
	char modified;
	char exit;
	char focused;
	TLine content;
    int linepos;
    int colpos;
} OpenedFileT;


// typedef struct settings{
	// background color
	// foreground color
//}
