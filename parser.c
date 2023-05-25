#include "parser.h"

// 20 bytes should be enough for all commands
#define BUFSIZE 20

// im sorry for this, but as far as i know
// i cant use switch cases for char arrays
inline static enum Commands interpret_command(char* str) {
    // we first look for the first character of the stirng,
    // then check for each one individually
    switch (str[0]) {
        case 'M':
            if (!strcmp(str, "MOVE_LEFT")) return MOVE_LEFT;
            if (!strcmp(str, "MOVE_LEFT_CHAR")) return MOVE_LEFT_CHAR;
            if (!strcmp(str, "MOVE_RIGHT")) return MOVE_RIGHT;
            if (!strcmp(str, "MOVE_RIGHT_CHAR")) return MOVE_RIGHT_CHAR;
            return UNDEFINED;
            break;
        case 'S':
            if (!strcmp(str, "SHOW")) return SHOW;
            if (!strcmp(str, "SHOW_CURRENT")) return SHOW_CURRENT;
            return UNDEFINED;
            break;
        case 'I':
            if (!strcmp(str, "INSERT_LEFT")) return INSERT_LEFT;
            if (!strcmp(str, "INSERT_RIGHT")) return INSERT_RIGHT;
            return UNDEFINED;
            break;
        default:
            // there are no more commands that begin with
            // the same letter
            if (!strcmp(str, "UNDO")) return UNDO;
            if (!strcmp(str, "REDO")) return REDO;
            if (!strcmp(str, "WRITE")) return WRITE;
            if (!strcmp(str, "EXECUTE")) return EXECUTE;
            return UNDEFINED;
            break;
    }
}

inline static char read_second_argument(FILE* fp) {
    // read the argument (C) of a command from the file
    char temp = 0;
    fscanf(fp, " %c", &temp);
    return temp;
}

TCmd get_command(FILE* fp) {
    // initialize the container for the command
    TCmd temp;
    temp.command = UNDEFINED;
    temp.arg1 = 0;
    // initialize the buffer for reading the command name
    char buffer[BUFSIZE] = {0};
    // get a command
    fscanf(fp, "%s", buffer);
    temp.command = interpret_command(buffer);
    switch (temp.command) {
        // if it is a command that requires an argument,
        // read the argument
        case MOVE_LEFT_CHAR:
        case MOVE_RIGHT_CHAR:
        case INSERT_LEFT:
        case INSERT_RIGHT:
        case WRITE:
            temp.arg1 = read_second_argument(fp);
            break;
        // otherwise dont do anything
        default:
            break;
    }
    // return the command container
    return temp;
}


// testing code
// int main(){
//     TCmd temp;
//     fprintf(OUTFILE, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",
//             UNDEFINED,
//             MOVE_LEFT,
//             MOVE_RIGHT,
//             SHOW_CURRENT,
//             SHOW,
//             UNDO,
//             REDO,
//             EXECUTE,
//             MOVE_LEFT_CHAR,
//             MOVE_RIGHT_CHAR,
//             WRITE,
//             INSERT_LEFT,
//             INSERT_RIGHT
//             );
//     do{
//         temp = get_command();
//         fprintf(OUTFILE, "%d, %d\n", temp.command, temp.arg1);
//     }while(temp.command != UNDEFINED);
// }
