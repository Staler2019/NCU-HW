%{
%}
sign        [+-]
digit       [0-9]
dot         \.
float       ^(({digit}+{dot}{digit}*)|({digit}*{dot}{digit}+))$
sci         ^(({digit}*{dot}{digit}*)|({digit}+))[Ee]{sign}?{digit}+$
eol         [\n\r]
%%
{sci}       {ECHO; printf("\n");}
{float}     {ECHO; printf("\n");}
{eol}       {;}
.           {;}
%%
int main(int argc, char *argv[]) {
    yylex();
    return 0;
}