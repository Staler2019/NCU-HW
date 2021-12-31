%{
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    void errorMat(int col);
    // yacc system
    void yyerror(const char *s);
    int yylex(void);
    void matCheck(void);
%}
%union{
    struct {
        int a;
        int b;
    } mat_val;

    int ival;
    char* sval;
}
%token  <ival>      INUMBER
%type   <mat_val>   mat
%left   <ival>      '+' '-'
%left   <ival>      '*'
%left               TRANS
%%
line        : mat
            |
            ;

mat         : '[' INUMBER ',' INUMBER ']'
                {
                    $$.a = $2;
                    $$.b = $4;
                }
            | '(' mat ')'
                {
                    $$.a = $2.a;
                    $$.b = $2.b;
                }
            | mat TRANS
                {
                    $$.a = $1.b;
                    $$.b = $1.a;
                }
            | mat '+' mat
                {
                    if($1.a != $3.a || $1.b != $3.b)
                        errorMat($2);
                    $$.a = $1.a;
                    $$.b = $1.b;
                }
            | mat '-' mat
                {
                    if($1.a != $3.a || $1.b != $3.b)
                        errorMat($2);
                    $$.a = $1.a;
                    $$.b = $1.b;
                }
            | mat '*' mat
                {
                    if($1.b != $3.a)
                        errorMat($2);
                    $$.a = $1.a;
                    $$.b = $3.b;
                }
            ;

%%
void yyerror(const char* s){
    fprintf(stderr, "%s\n", s);
}

void errorMat(int col){
    printf("Semantic error on col %d\n", col);
    exit(0);
}

int main(){
    yyparse();

    printf("Accepted\n");

    return 0;
}