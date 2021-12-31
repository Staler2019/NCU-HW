%{
    #include "main.tab.h"
    #include <string.h>
    int col;
%}
%%
[0-9]+      { yylval.ival = atoi(yytext); col += yyleng; return(INUMBER); }
"^T"        { col += yyleng; return(TRANS); }
" "         { col += yyleng; }
'\n'        { col = 0; }
'\r'        { ; }
[\+\-\*]    { col += yyleng; yylval.ival = col; return(yytext[0]); }
.           { col += yyleng; return(yytext[0]); }
%%