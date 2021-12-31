SHELL	:= /bin/bash
CC		:= gcc
LEX		:= flex
YACC 	:= bison

YFLAGS	:= -c -g
LFLAGS	:= -c -g
INC 	:= -I..

FNAME 	:= main
FTEST	:= 110HW3_B5.in
FERR	:= error.err

.PHONY: all clear clean

all: $(FNAME)
	./$(FNAME) < $(FTEST) 2> $(FERR)

$(FNAME): yacc.tab.o lex.yy.o
	$(CC) -o $(FNAME) $(FNAME).tab.o lex.yy.o -ll

yacc.tab.o: $(FNAME).y
	$(YACC) -d -o $(FNAME).tab.c $(FNAME).y
	$(CC) $(YFLAGS) $(INC) $(FNAME).tab.c

lex.yy.o: $(FNAME).l
	$(LEX) -o lex.yy.c $(FNAME).l
	$(CC) $(LFLAGS) $(INC) lex.yy.c

clear:
	-rm -f *.o *.tab.c *.tab.h *.yy.c

clean: clear
	-rm -f $(FNAME) $(FERR)