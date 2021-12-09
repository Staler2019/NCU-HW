# !/bin/bash
flex  ./md.l
gcc lex.yy.c -lfl
./a.out < ./110BA2_C3.in