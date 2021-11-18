# !/bin/bash
flex -o ./main.lex.yy.c ./main.l
gcc -o ./main.out ./main.lex.yy.c -lfl
./main.out < ./110HW2_A3.in