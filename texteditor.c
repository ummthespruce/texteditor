#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include "types.h"
#include "line.h"
#include "io.h"

#define MAXFILENAMESIZE 30
#define MAXLINENUMBERSIZE 4
#define MAXFILENAMELINES 2
#define MAXSTATELINES 2

void init_FW(OpenedFileT *op) {
	getmaxyx(stdscr, op->FW.yMax, op->FW.xMax);
	getbegyx(stdscr, op->FW.yBeg, op->FW.xBeg);

	// create a window for file name
	// 1 line for file name, leave 1 line for border
	op->FW.filewin = newwin(MAXFILENAMELINES,
							MAXFILENAMESIZE + 1,
							op->FW.yBeg,
							op->FW.xBeg);
	wborder(op->FW.filewin, ' ', ' ', ' ', '-', ' ', ' ', '-', '-');
    if (op->filename) {
        wprintw(op->FW.filewin, "%.*s", MAXFILENAMESIZE + 1, op->filename);
    }


	// create a window for lines
	// has a defined width
	op->FW.linewin = newwin(op->FW.yMax - MAXFILENAMELINES - MAXSTATELINES,
							MAXLINENUMBERSIZE + 1,
							op->FW.yBeg + MAXFILENAMELINES,
							op->FW.xBeg);
	wborder(op->FW.linewin, ' ', '|', ' ', ' ', ' ', '|', ' ', '|');


	// create a window for the file content
	// as much as we can
	op->FW.contentwin = newwin(op->FW.yMax - MAXFILENAMELINES - MAXSTATELINES,
								op->FW.xMax - MAXLINENUMBERSIZE - 1,
								op->FW.yBeg + MAXFILENAMELINES,
								op->FW.xBeg + MAXLINENUMBERSIZE + 1);


	// create a window for the state (cursor position, mode etc)
	op->FW.statewin = newwin(MAXSTATELINES,
						op->FW.xMax,
						op->FW.yMax - MAXSTATELINES,
						op->FW.xBeg
	);
	// wborder(op->FW.statewin, 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p');


	// curs_set() // [0;2]
}
void update(OpenedFileT *op) {
	// write new info

	// filename
    int len = 0;
    if (op->filename) {
        mvwprintw(op->FW.filewin, 0, 0, "%.*s", MAXFILENAMESIZE + 1, op->filename);
        len = strlen(op->filename);
        if (len > MAXFILENAMESIZE) {
            len = MAXFILENAMESIZE;
        }
    }
    if (op->modified) {
        mvwprintw(op->FW.filewin, 0, len, "*");
    }

	// content
    // check to see if current line is in view, and if it is not,
    // move it
    // max one move per "frame"
    int maxlines = op->FW.yMax - MAXFILENAMELINES - MAXSTATELINES;
    int maxcols = op->FW.xMax - MAXLINENUMBERSIZE - 1;
    // int xConBegin = op->FW.xBeg + MAXLINENUMBERSIZE + 1;
    // int yConBegin = op->FW.yBeg + MAXFILENAMELINES;

    if(!op->linepos) {
        op->linepos = 1;
        op->content->linepos = op->content->sentry->next;
    }
    if (op->content->posy < op->linepos) {
        op->linepos--;
        op->content->linepos = op->content->linepos->prev;
    } else if (op->content->posy > op->linepos + maxlines) {
        op->linepos++;
        op->content->linepos = op->content->linepos->next;
    }
    // now that check if the cursor is in view

    if (op->content->posx < op->colpos) {
        op->colpos--;
    } else if (op->content->posx > op->colpos + maxcols) {
        op->colpos++;
    }

    mvwprintw(op->FW.statewin, 0, 0, "                                                ");

    // mvwprintw(op->FW.statewin, 0, 8, "%d", op->linepos);
    // mvwprintw(op->FW.statewin, 0, 12, "%d", op->colpos);
    // now cursor is in view, clear content
    // and print all the lines and collumns in view

	for(int i = 0; i < maxlines; i++) {
		for (int j = 0; j < maxcols; j++) {
			mvwprintw(op->FW.contentwin, i, j, " ");
		}
	}

	TDLListL templine = op->content->linepos;
	TDLListT temptape = 0;
	for(int i = 0; templine && i < maxlines; templine = templine->next, i++) {
		temptape = templine->value->sentry->next;
        for (int j = 0; temptape && j < op->colpos - 1; temptape = temptape->next, j++){

        }
		for (int j = 0; temptape && j < maxcols; temptape = temptape->next, j++) {
			mvwprintw(op->FW.contentwin, i, j, "%c", temptape->value);
		}
	}

    // print lines

    for(int i = 0; i < maxlines; i++) {
        mvwprintw(op->FW.linewin, i, 0, "%d", i + op->linepos);
        for (int j = 0; j < MAXLINENUMBERSIZE; j++) {
            mvwprintw(op->FW.linewin, i, j, " ");
        }
        mvwprintw(op->FW.linewin, i, 0, "%d", i + op->linepos);
    }

	// check if



	// state print position and insert

    // mvwprintw(op->FW.statewin, 0, 0, "%d", op->content->posx);
    // mvwprintw(op->FW.statewin, 0, 4, "%d", op->content->posy);
    // mvwprintw(op->FW.statewin, 0, 16, "%p", op->content->cursor);
    // mvwprintw(op->FW.statewin, 0, 32, "%p", op->content->finger->value->sentry);

	wnoutrefresh(op->FW.filewin);
	wnoutrefresh(op->FW.linewin);
	wnoutrefresh(op->FW.contentwin);
	wnoutrefresh(op->FW.statewin);

	doupdate();

    wmove(op->FW.contentwin, op->content->posy - op->linepos, op->content->posx - op->colpos);
    wrefresh(op->FW.contentwin);
    // move cursor to position

}


void remove_window_info(OpenedFileT *op) {
    werase(op->FW.filewin);
    werase(op->FW.linewin);
    werase(op->FW.contentwin);
    werase(op->FW.statewin);

    wnoutrefresh(op->FW.filewin);
    wnoutrefresh(op->FW.linewin);
    wnoutrefresh(op->FW.contentwin);
    wnoutrefresh(op->FW.statewin);

    delwin(op->FW.linewin);
    delwin(op->FW.filewin);
    delwin(op->FW.contentwin);
    delwin(op->FW.statewin);

    doupdate();
}

int main(int argc, char *argv[]) {

	OpenedFileT op;
	op.exit = 0;
	op.modified = 0;
	op.focused = 0;
	if (argc > 1) {
		op.filename = calloc(1,strlen(argv[1]));
		strcpy(op.filename, argv[1]);
	} else {
        op.filename = 0;
    }
	op.content = readfile(op.filename);
    if (!op.content) {
        op.modified = 1;
        op.content = init_line();
    }
    op.linepos = 0;
    op.colpos = 1;

	// save -> ask for filename if its not set
	
	// ncurses begin
	initscr();
		// let program choose what to do with characters
	noecho();
	cbreak();
    keypad(stdscr, true);

	init_FW(&op);;

	update(&op);
    int key = 1;
	wmove(op.FW.contentwin,0,0);
	while(key) {
        key = getch();
        switch(key) {
            case KEY_RIGHT:
                move_right(op.content);
                break;
            case KEY_UP:
                move_up(op.content, 0);
                break;
            case KEY_DOWN:
                move_down(op.content, 0);
                break;
            case KEY_LEFT:
                move_left(op.content);
                break;
            case '\n':
            case '\r':
                create_down(op.content);
                move_down(op.content,1);
                break;
            case KEY_BACKSPACE:
            case KEY_DC:
            case 127:
                delete_character_on_cursor(op.content);
                break;
            case KEY_F(5):
                delete_line_on_finger(op.content);
                break;
            case KEY_F(6):
                writefile(op.filename, op.content);
                endwin();
                return 0;
            default:
                create_on_cursor(op.content, key);
                break;
            // key left move left
            //
        }
        update(&op);

    }
    endwin();
    free_line(op.content);

    return 0;
}
