CC=gcc
CFLAGS= -g -Wall -lcurses

DEPSSRC=tape.c line.c io.c
DEPS+=$(DEPSSRC:.c=.h)
DEPS+=types.h
DEPSOBJ=$(DEPSSRC:.c=.o)

EXE=texteditor
SRC=$(EXE:=.c)
OBJ=$(SRC:.c=.o)

VGLOGFILE=valgrind.txt

build: $(DEPSOBJ) $(OBJ)
	$(CC) -o $(EXE) $^ $(CFLAGS)

run: $(EXE)
	./$(EXE)

clean:
	rm -f *.o $(EXE)

zip:
	zip -r homework.zip \
	Makefile README \
	*.c *.h

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)


$(EXE): $(DEPSOBJ) $(OBJ)
	$(CC) $(DEPSOBJ) $@.o -o $@ $(CFLAGS)

.PHONY: clean

style: cpplint clangtidy

valgrind: exec
	valgrind --leak-check=full \
	--track-origins=yes \
	--verbose \
	--log-file=$(VGLOGFILE) \
	./$(EXE)

cpplint: $(DEPSSRC) $(DEPS) $(SRC)
	-cpplint --filter=-legal/copyright,-readability/casting,-build/include_subdir,-runtime/threadsafe_fn,-build/header_guard,-runtime/int \
	--linelength=120 $^

clangtidy: $(DEPSSRC) $(DEPS) $(SRC)
	-clang-tidy -checks='-*,cppcoreguidelines*' \
	--warnings-as-errors='-*,cppcoreguidelines*'\
	$(DEPSSRC) $(DEPS) $(SRC)






