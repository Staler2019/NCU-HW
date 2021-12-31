%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct int_stack_def{
    #define STACKSIZE 1000
    int members[STACKSIZE];
    int si;
};
typedef struct int_stack_def int_stack;

int_stack st;

int stsize(){
    return st.si;
}
void stpop(){
    st.si--;
}
int sttop(){
    return st.members[st.si-1];
}
void stpush(int a){
    st.members[st.si++] = a;
}


void yyerror(const char *s);
int yylex(void);
void stackError();
%}
%union{
    int ival;
}
%token <ival> INUMBER
%token LD
%token ADD
%token SUB
%token MUL
%token MOD
%token INC
%token DEC
%%
STMTS: STMT '\n' STMTS | ;
STMT:
    LD INUMBER  { stpush($2); }
|   ADD
    {
        if(stsize() < 2)
            stackError();
        int a = sttop();
        stpop();
        int b = sttop();
        stpop();
        stpush(a+b);
    }
|   SUB
    {
        if(stsize() < 2)
            stackError();
        int a = sttop();
        stpop();
        int b = sttop();
        stpop();
        stpush(a-b);
    }
|   MUL
    {
        if(stsize() < 2)
            stackError();
        int a = sttop();
        stpop();
        int b = sttop();
        stpop();
        stpush(a*b);
    }
|   MOD
    {
        if(stsize() < 2)
            stackError();
        int a = sttop();
        stpop();
        int b = sttop();
        stpop();
        stpush(a%b);
    }
|   INC
    {
        if(stsize() < 1)
            stackError();
        int a = sttop();
        stpop();
        stpush(++a);
    }
|   DEC
    {
        if(stsize() < 1)
            stackError();
        int a = sttop();
        stpop();
        stpush(--a);
    }
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
    st.si = 0;

    yyparse();

    if(stsize() == 1)
        printf("%d\n", sttop());
    else
        printf("Invalid format\n");

    return(0);
}