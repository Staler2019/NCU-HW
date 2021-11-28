# !/bin/bash
flex  ./main.l
gcc lex.yy.c -lfl
./a.out < ./110HW2_A3.in