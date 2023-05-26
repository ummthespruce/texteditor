#include <stdio.h>
#include "openedfile.h"
/*
#include "types.h"
#include "commands.h"
#include "parser.h"
*/

int main(int argc, char *argv[]) {

	// FW
	OpenedFileT op;
	op.exit = 0;
	op.modified = 0
	op.focused = 0;
	if (argc > 1) {
		op.filename = calloc(1,strlen(argv[1]));
		strcpy(op.filename, argv[1]);
	}
	op.content = init_line();
	
	// save -> ask for filename if its not set
	
	// ncurses begin
	initscr();
		// let program choose what to do with characters
	noecho();
	cbreak();
	
	init_FW(op);
	update(OpenedFileT)
	
	getch();
	remove_window_info(OpenedFileT);
	getch();
	endwin();
	
	while()
	
	
	/*
	if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    exit(1);
	}
	COLOR_BLACK
    COLOR_RED
    COLOR_GREEN
    COLOR_YELLOW
    COLOR_BLUE
    COLOR_MAGENTA
    COLOR_CYAN
    COLOR_WHITE
	*/
	
	
	/*
	
    // declaring heap variables
    TLine line = init_line();
    TQueue cmdqueue = init_queue();
    TUR ur = init_ur();
    FILE* INfp = fopen(INFILE, "r");
    FILE* OUTfp = fopen(OUTFILE, "w");
    // reading number of commands
    fscanf(INfp, "%d", &n);
    int i = 0;
    // reading command
    for (; i < n; i++) {
        cmdbuf = get_command(INfp);
        // choosing what to do with command:
        switch (cmdbuf.command) {
            // UPDATE type commands get queued
            case MOVE_LEFT:
            case MOVE_RIGHT:
            case MOVE_LEFT_CHAR:
            case MOVE_RIGHT_CHAR:
            case INSERT_LEFT:
            case INSERT_RIGHT:
            case WRITE:
                enqueue(cmdqueue, cmdbuf);
                break;

            // the rest get executed immediately
            case SHOW_CURRENT:
                show_current_command(tape, OUTfp);
                break;
            case SHOW:
                show_command(tape, OUTfp);
                break;
            case UNDO:
                undo_command(tape, ur);
                break;
            case REDO:
                redo_command(tape, ur);
                break;
            case EXECUTE:
                execute(tape, ur, cmdqueue, OUTfp);
                break;
            case UNDEFINED:
                fprintf(OUTfp, "BIGERROR IN MAIN, UNDEFINED COMMAND!\n");
                return 0;
                break;
            default:
                fprintf(OUTfp, "BIGERROR IN MAIN, DEFAULT CASE REACHED!\n");
                return 0;
                break;
        }
    }
    free_ur(ur);
    free_queue(cmdqueue);
    free_tape(tape);
    fclose(INfp);
    fclose(OUTfp);*/
	
	
    return 0;
}
