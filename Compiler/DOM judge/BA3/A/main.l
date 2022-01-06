%{
#include "main.tab.h"
%}
%%
[0-9]+       { yylval.ival = atoi(yytext); return(INUMBER); }
"push"      { return(PUSH); }
"inverse"   { return(INV); }
"inc"       { return(INC); }
"dec"       { return(DEC); }
[\n]        { ; }
[\$]        { return yytext[0]; }
[ \t\r]+    { ; }
.           { ; }
%%