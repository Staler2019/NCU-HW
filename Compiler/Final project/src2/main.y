%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct pair {
    char* name;
    int value;
};

struct pair p[30];
int pair_size = 0;

int findPair(char* str){
    for(int i = 0; i < pair_size; i++){
        if(strcmp(p[i].name, str) == 0){
            return i;
        }
    }
    return -1;
}

int equ_status;

void yyerror(const char *s);
int yylex(void);
%}
%union{
    int ival;
    char* sval;
}
%token  <ival>      NUMBER
%token  <ival>      BOOL_VAL
%token  <sval>      ID
%token  PLUS MINUS MULTIPLY DIVIDE MODULUS GREATER SMALLER EQUAL AND OR NOT DEFINE FUN IF LEFT_BRACKET RIGHT_BRACKET PRINT_NUM PRINT_BOOL
%type   <ival>      program stmts stmt exp def_stmt print_stmt num_op fun_exp fun_ids fun_body fun_name fun_call
%type   <ival>      variable id_s exps param_s param
%type   <ival>      plus minus multiply divide modulus greater smaller equal if_exp test_exp than_exp else_exp logical_op and_op or_op not_op exps_plus exps_mul exps_and exps_or exps_equ
%%
program:
    stmts
    ;
stmts:
    stmt stmts
    |
    ;
stmt:
    exp
    | def_stmt
    | print_stmt
    ;
print_stmt:
    LEFT_BRACKET PRINT_NUM exp RIGHT_BRACKET {
        printf("%d\n", $3);
    }
    | LEFT_BRACKET PRINT_BOOL exp RIGHT_BRACKET {
        printf("%s\n", ($3)?"#t":"#f");
    }
    ;
exp:
    BOOL_VAL
    | NUMBER
    | variable { $$ = p[$1].value; }
    | num_op
    | logical_op
    | fun_exp
    | fun_call
    | if_exp
    ;
num_op:
    plus
    | minus
    | multiply
    | divide
    | modulus
    | greater
    | smaller
    | equal
    ;
plus:
    LEFT_BRACKET PLUS exp exps_plus RIGHT_BRACKET {
        $$ = $3 + $4;
    }
    ;
exps_plus:
    exp exps_plus{
        $$ = $1 + $2;
    }
    | exp { $$ = $1; }
    ;
minus:
    LEFT_BRACKET MINUS exp exp RIGHT_BRACKET {
        $$ = $3 - $4;
    }
    ;
multiply:
    LEFT_BRACKET MULTIPLY exp exps_mul RIGHT_BRACKET {
        $$ = $3 * $4;
    }
    ;
exps_mul:
    exp exps_mul {
        $$ = $1 * $2;
    }
    | exp { $$ = $1; }
    ;
divide:
    LEFT_BRACKET DIVIDE exp exp RIGHT_BRACKET {
        $$ = $3 / $4;
    }
    ;
modulus:
    LEFT_BRACKET MODULUS exp exp RIGHT_BRACKET {
        $$ = $3 % $4;
    }
    ;
greater:
    LEFT_BRACKET GREATER exp exp RIGHT_BRACKET {
        $$ = $3 > $4;
    }
    ;
smaller:
    LEFT_BRACKET SMALLER exp exp RIGHT_BRACKET {
        $$ = $3 < $4;
    }
    ;
equal:
    LEFT_BRACKET EQUAL {equ_status = 1;} exp exps_equ RIGHT_BRACKET {
        if($4 != $5)
            equ_status = 0;
        $$ = equ_status;
    }
    ;
exps_equ:
    exp exps_equ {
        if($1 != $2)
            equ_status = 0;
        $$ = $1;
    }
    | exp {
        $$ = $1;
    }
exps:
    exp exps
    |
    ;
logical_op:
    and_op
    | or_op
    | not_op
    ;
and_op:
    LEFT_BRACKET AND exp exps_and RIGHT_BRACKET {
        $$ = $3 && $4;
    }
    ;
exps_and:
    exp exps_and {
        $$ = $1 && $2;
    }
    | exp { $$ = $1; }
    ;

or_op:
    LEFT_BRACKET OR exp exps_or RIGHT_BRACKET {
        $$ = $3 || $4;
    }
    ;
exps_or:
    exp exps_or {
        $$ = $1 || $2;
    }
    | exp { $$ = $1; }
    ;
not_op:
    LEFT_BRACKET NOT exp RIGHT_BRACKET {
        $$ = !$3;
    }
    ;
def_stmt:
    LEFT_BRACKET DEFINE variable exp RIGHT_BRACKET {
            p[$3].value = $4;
    }
    ;
variable:
    ID {
        int tmp = findPair($1);
        // printf("%d\n",tmp);
        if(tmp == -1){
            if(pair_size<30){
                p[pair_size++].name = $1;
                $$ =  pair_size-1;
            }
            else {
                printf("var table error");
            }
        }else {
            $$ = tmp;
        }
    }
    ;
fun_exp:
    LEFT_BRACKET FUN fun_ids fun_body RIGHT_BRACKET
    ;
fun_ids:
    LEFT_BRACKET id_s RIGHT_BRACKET
    ;
fun_body:
    exp
    ;
id_s:
    ID id_s
    |
    ;
fun_call:
    LEFT_BRACKET fun_exp param_s RIGHT_BRACKET
    | LEFT_BRACKET fun_name param_s RIGHT_BRACKET
    ;
fun_name:
    ID
    ;
param_s:
    param param_s
    |
    ;
param:
    exp
    ;
if_exp:
    LEFT_BRACKET IF test_exp than_exp else_exp RIGHT_BRACKET {
        $$ = ($3) ? $4 : $5;
    }
    ;
test_exp:
    exp
    ;
than_exp:
    exp
    ;
else_exp:
    exp
    ;
%%
void yyerror(const char* s){
    fprintf(stderr, "%s\n", s);
}

int main() {

    yyparse();

    return(0);
}