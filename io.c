#include "io.h"

#define DEBUGIO

char add_buffer_to_tape(char *string, TDLListT *last) {
	char nlflag = 0;
	TDLListT prev = *last;
	TDLListT temp = 0;
	int i = 0;
	for (; string[i] ; i++) {
		if (string[i] != '\n') {
			temp = aloc_tape_cell(string[i]);
			if (prev) {
				prev->next = temp;
				temp->prev = prev;
			}
			prev = temp;
		} else {
			nlflag = 1;
			break;
		}
	}
	*last = prev;
	return nlflag;
}


TLine readfile(const char *filename) {
	char buffer[1000];
	FILE* file = fopen(filename, "r");
	if (!file) {
		return 0;
	}
	TLine temp = init_line();
	TDLListT last = temp->finger->value->sentry;
	while (fgets(buffer, 1000, file)) {
#ifdef DEBUGIO
		printf("%s", buffer);
        printf("%p\n", temp->finger);
#endif
		char nl = add_buffer_to_tape(buffer, &last);
		if (nl) {
			create_down(temp);
            move_down(temp, 1);
			last = temp->finger->value->sentry;
		}
	}
	// TODO delete current line and move back up
	return temp;
	fclose(file);
}

void writefile(const char *filename, TLine line) {
	// go past the line sentry
	TDLListL templine = line->sentry->next;
	TDLListT temptape = 0;
	FILE* filep = fopen(filename, "w");
	for(; templine; templine = templine->next) {
		temptape = templine->value->sentry->next;
		for (; temptape; temptape = temptape->next) {
			fprintf(filep, "%c", temptape->value);
		}
		fprintf(filep, "\n");
	}
	fclose(filep);
}

