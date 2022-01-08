%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);
%}
%union{
}
%token  <ival>      NUMBER
%token  <bval>      BOOL_VAL
%token  <strval>    ID
%token  PLUS MINUS MULTIPLY DIVIDE MODULUS GREATER SMALLER EQUAL AND OR NOT DEFINE FUN IF LEFT_BRACKET RIGHT_BRACKET PRINT_NUM PRINT_BOOL
%type   <nval>      program stmts stmt exp def_stmt print_stmt num_op fun_exp fun_ids fun_body fun_name fun_call
%type   <nval>      variable id_s exps param_s param
%type   <nval>      plus minus multiply divide modulus greater smaller equal if_exp test_exp than_exp else_exp logical_op and_op or_op not_op
%%
program:
    stmts {
        root = $1;
    }
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
    LEFT_BRACKET PRINT_NUM exp RIGHT_BRACKET
    | LEFT_BRACKET PRINT_BOOL exp RIGHT_BRACKET
    ;
exp:
    BOOL_VAL
    | NUMBER
    | variable
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
    LEFT_BRACKET PLUS exp exps RIGHT_BRACKET
    ;
minus:
    LEFT_BRACKET MINUS exp exp RIGHT_BRACKET
    ;
multiply:
    LEFT_BRACKET MULTIPLY exp exps RIGHT_BRACKET
    ;
divide:
    LEFT_BRACKET DIVIDE exp exp RIGHT_BRACKET
    ;
modulus:
    LEFT_BRACKET MODULUS exp exp RIGHT_BRACKET
    ;
greater:
    LEFT_BRACKET GREATER exp exp RIGHT_BRACKET
    ;
smaller:
    LEFT_BRACKET SMALLER exp exp RIGHT_BRACKET
    ;
equal:
    LEFT_BRACKET EQUAL exp exps RIGHT_BRACKET
    ;
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
    LEFT_BRACKET AND exp exps RIGHT_BRACKET
    ;
or_op:
    LEFT_BRACKET OR exp exps RIGHT_BRACKET
    ;
not_op:
    LEFT_BRACKET NOT exp RIGHT_BRACKET
    ;
def_stmt:
    LEFT_BRACKET DEFINE variable exp RIGHT_BRACKET
    ;
variable:
    ID
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
    LEFT_BRACKET IF test_exp than_exp else_exp RIGHT_BRACKET
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
void stackError(){
    printf("Invalid format\n");
    exit(0);
}

void yyerror(const char* s){
    fprintf(stderr, "%s\n", s);
}

int main() {

    yyparse();

    return(0);
}