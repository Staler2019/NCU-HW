%option noyywrap
%{
#include "main.tab.h"
#include <string.h>
%}
plus            "+"
minus           "-"
multiply        "*"
divide          "/"
modulus         "mod"
greater         ">"
smaller         "<"
equal           "="
and             "and"
or              "or"
not             "not"
define          "define"
fun             "fun"
if              "if"
separator       [\t\n\r ]
letter          [a-z]
digit           [0-9]
number          0|[1-9]{digit}*|-[1-9]{digit}*
ID              {letter}({letter}|{digit}|-)*
bool-val        "#t"|"#f"
left_bracket    "("
right_bracket   ")"
print_num       "print-num"
print_bool      "print-bool"
%%
{plus}          { return PLUS; }
{minus}         { return MINUS; }
{multiply}      { return MULTIPLY; }
{divide}        { return DIVIDE; }
{modulus}       { return MODULUS; }
{greater}       { return GREATER; }
{smaller}       { return SMALLER; }
{equal}         { return EQUAL; }
{and}           { return AND; }
{or}            { return OR; }
{not}           { return NOT; }
{define}        { return DEFINE; }
{fun}           { return FUN; }
{if}            { return IF; }
{separator}     { ; }
{number}        { yylval.ival = atoi(yytext); return NUMBER; }
{print_num}     { return PRINT_NUM; }
{print_bool}    { return PRINT_BOOL; }
{bool-val}      {
    if(strcmp(yytext, "#t") == 0)
        yylval.ival = 1;
    else if (strcmp(yytext, "#f") == 0)
        yylval.ival = 0;
    return BOOL_VAL;
}
{left_bracket}  { return LEFT_BRACKET; }
{right_bracket} { return RIGHT_BRACKET; }
{ID}            { yylval.sval = strdup(yytext); return ID; }
.               { ; }
%%