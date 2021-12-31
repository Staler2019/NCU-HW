%{
#include "main.tab.h"
%}
%%
[0-9]+       { yylval.ival = atoi(yytext); return(INUMBER); }
"load"      { return(LD); }
"add"       { return(ADD); }
"sub"       { return(SUB); }
"mul"       { return(MUL); }
"mod"       { return(MOD); }
"inc"       { return(INC); }
"dec"       { return(DEC); }
[\n]        { return yytext[0]; }
[ \t\r]+    { ; }
.           { ; }
%%