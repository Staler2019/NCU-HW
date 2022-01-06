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
void stinverse(){
    // int_stack tmp = st;
    // for(int i = st.si-1; i >= 0; i--){
    //     st.members[st.si-1-i] = tmp.members[i];
    // }
    int tmp1 = sttop();
    stpop();
    int tmp2 = sttop();
    stpop();
    stpush(tmp1);
    stpush(tmp2);
}


void yyerror(const char *s);
int yylex(void);
void stackError();
%}
%union{
    int ival;
}
%token <ival> INUMBER
%token PUSH
%token INV
%token INC
%token DEC
%%
STMTS: STMT STMTS | '$' ;
STMT:   PUSH INUMBER {
        stpush($2);
    }
    |   INV {
        stinverse();
    }
    |   INC {
            if(stsize() < 1)
                stackError();
            int a = sttop();
            stpop();
            stpush(++a);
        }
    |   DEC {
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

    // if(stsize() == 1)
    printf("%d\n", sttop());
    // else
    //     printf("Invalid format\n");

    return(0);
}