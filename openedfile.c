#include "openedfile.h"

void init_FW(OpenedFileT op) {
	getmaxyx(stdscr, op.FW.yMax, op.FW.xMax);
	getbegyx(stdscr, op.FW.yBeg, op.FW.xBeg);
	
	// create a window for file name
	// 1 line for file name, leave 1 line for border
	op.FW.filewin = newwin(MAXFILENAMELINES,
							MAXFILENAMESIZE + 1,
							yBeg,
							xBeg);
	wborder(FW.filewin, 0, 0, 0, '-', 0, 0, '-', '-');
    wprintw(FW.filewin, "%.*s", MAXFILENAMESIZE + 1, teststring);	
	 
	// create a window for lines
	// has a defined width
	op.FW.linewin = newwin(yMax - MAXFILENAMELINES - MAXSTATELINES,
							MAXLINENUMBERSIZE + 1,
							yBeg + MAXFILENAMELINES,
							xBeg);
	wborder(FW.linewin, '|', '|', '-', '-', '.', '.', '.', '.');

	// create a window for the file content
	// as much as we can
	op.FW.contentwin = newwin(yMax - MAXFILENAMELINES - MAXSTATELINES,
								xMax - MAXLINENUMBERSIZE - 1,
								yBeg + MAXFILENAMELINES,
								xBeg + MAXLINENUMBERSIZE + 1);
    wborder(FW.contentwin, 'h', 'a', 'b', 'c', 'd', 'e', 'f', 'g');
	
	// create a window for the state (cursor position, mode etc)
	op.FW.statewin = newwin(MAXSTATELINES,
						xMax,
						yBeg - MAXSTATELINES,
						xbeg 		
	);
	wborder(FW.statewin, 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p');
	
	
	// curs_set() // [0;2]
}
	
void update(OpenedFileT op) {
	wclear(FW.filewin);
	wclear(FW.linewin);
	wclear(FW.contentwin);
	wclear(FW.statewin);
	
	// write new info
	
	// filename
	
	// lines
	
	// check if 
	
	// content
	
	// state
	
	wnoutrefresh(op.FW.filewin);
	wnoutrefresh(op.FW.linewin);
	wnoutrefresh(op.FW.contentwin);
	wnoutrefresh(op.FW.statewin);
	doupdate();
}
	

void remove_window_info(OpenedFileT op) {
    werase(op.FW.filewin);
    wnoutrefresh(op.FW.filewin);
    delwin(op.FW.filewin);

    werase(op.FW.linewin);
    wnoutrefresh(op.FW.linewin);
    delwin(op.FW.linewin);
	
    werase(op.FW.contentwin);
    wnoutrefresh(op.FW.contentwin);
    delwin(op.FW.contentwin);

    werase(op.FW.statewin);
    wnoutrefresh(op.FW.statewin);
    delwin(op.FW.statewin);

    doupdate();
}
    
