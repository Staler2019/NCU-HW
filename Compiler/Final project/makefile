SHELL		:= /bin/bash
CC			:= g++
LEX			:= flex
YACC 		:= bison

INC 		:= -I.. -I./src/
YFLAGS		:= -c -g $(INC)
LFLAGS		:= -c -g $(INC)
CFLAGS		:= -ll

BUILD_DIR	:= ./build
SRC_DIR		:= ./src
YNAME		:= yacc
LNAME		:= lex
SNAME		:= struct
FNAME 		:= myMiniLisp
OBJS		:= $(BUILD_DIR)/$(YNAME).tab.o $(BUILD_DIR)/$(LNAME).yy.o
PROCESS		:= $(BUILD_DIR)/$(FNAME)

FTEST		:= input.in
FERR		:= error.err

.PHONY: all clean

all: $(PROCESS)
	$(PROCESS) < $(FTEST) 2> $(FERR)

$(PROCESS): $(OBJS)
	$(CC) -o $(PROCESS) $(OBJS) $(CFLAGS)

$(BUILD_DIR)/$(YNAME).tab.o: $(SRC_DIR)/$(FNAME).y $(SRC_DIR)/$(SNAME).h
	$(YACC) -d -o $(BUILD_DIR)/$(YNAME).tab.c $(SRC_DIR)/$(FNAME).y
	$(CC) $(YFLAGS) $(BUILD_DIR)/$(YNAME).tab.c

$(BUILD_DIR)/lex.yy.o: $(SRC_DIR)/$(FNAME).l $(SRC_DIR)/$(SNAME).h
	$(LEX) -o $(BUILD_DIR)/$(LNAME).yy.c $(FNAME).l
	$(CC) $(LFLAGS) $(BUILD_DIR)/$(LNAME).yy.c

clean:
	@-rm -rf $(BUILD_DIR)