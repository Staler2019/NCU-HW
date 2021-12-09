# !/bin/bash
flex  ./float.l
gcc lex.yy.c -lfl
./a.out < ./test.in