SHELL		:= /bin/bash
CC			:= g++
LEX			:= flex
YACC 		:= bison

BUILD_DIR	:= ./build
SRC_DIR		:= ./src
TEST_DIR	:= ../test_data

# INC 		:= -I$(BUILD_DIR)
# YFLAGS		:= -c -g $(INC)
# LFLAGS		:= -c -g $(INC)
YFLAGS		:= -c -g
LFLAGS		:= -c -g
CFLAGS		:= -ll

SNAME		:= struct
FNAME 		:= myMiniLisp
TNAME		:= 06_2.lsp
OBJS		:= yacc.tab.o lex.yy.o
PROCESS		:= $(FNAME)

FTEST		:= $(TEST_DIR)/$(TNAME)
FERR		:= error.err

.PHONY: all clean

all: $(PROCESS)
	./$(PROCESS) < $(FTEST) 2> $(FERR)

$(PROCESS): $(OBJS)
	$(CC) -o $(PROCESS) $(OBJS) $(CFLAGS)

lex.yy.o: lex.yy.c yacc.tab.h $(SNAME).h
	$(CC) $(LFLAGS) lex.yy.c

yacc.tab.o: yacc.tab.c $(SNAME).h
	$(CC) $(YFLAGS) yacc.tab.c

yacc.tab.c yacc.tab.h: $(FNAME).y
	$(YACC) -d -o yacc.tab.c $(FNAME).y

lex.yy.c: $(FNAME).l
	$(LEX) -o lex.yy.c $(FNAME).l

# $(BUILD_DIR)/yacc.tab.o: $(BUILD_DIR)/yacc.tab.c $(BUILD_DIR)/$(SNAME).h
# 	$(CC) $(YFLAGS) $(BUILD_DIR)/yacc.tab.c $(BUILD_DIR)/$(SNAME).h -o $(BUILD_DIR)/yacc.tab.o

# $(BUILD_DIR)/lex.yy.o: $(BUILD_DIR)/lex.yy.c $(BUILD_DIR)/yacc.tab.h $(BUILD_DIR)/$(SNAME).h
# 	$(CC) $(LFLAGS) $(BUILD_DIR)/lex.yy.c $(BUILD_DIR)/yacc.tab.h $(BUILD_DIR)/$(SNAME).h -o lex.yy.o

# $(BUILD_DIR)/yacc.tab.c $(BUILD_DIR)/yacc.tab.h: $(BUILD_DIR)/$(FNAME).y
# 	$(YACC) -d -o $(BUILD_DIR)/yacc.tab.c $(BUILD_DIR)/$(FNAME).y

# $(BUILD_DIR)/lex.yy.c: $(BUILD_DIR)/$(FNAME).l
# 	$(LEX) -o $(BUILD_DIR)/lex.yy.c $(BUILD_DIR)/$(FNAME).l

# $(BUILD_DIR)/$(SNAME).h: $(SRC_DIR)/$(SNAME).h
# 	@cp $(SRC_DIR)/$(SNAME).h $(BUILD_DIR)/$(SNAME).h

# $(BUILD_DIR)/$(FNAME).y: $(SRC_DIR)/$(FNAME).y
# 	@cp $(SRC_DIR)/$(FNAME).y $(BUILD_DIR)/$(FNAME).y

# $(BUILD_DIR)/$(FNAME).l: $(SRC_DIR)/$(FNAME).l
# 	@cp $(SRC_DIR)/$(FNAME).l $(BUILD_DIR)/$(FNAME).l

clean:
	@-rm *.yy.c *.yy.o *.tab.c *.tab.h *.tab.o $(PROCESS) $(FERR)

# pre_build:
# 	@mkdir -p $(BUILD_DIR)