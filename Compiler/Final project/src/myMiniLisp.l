%option noyywrap
%{
#include "struct.h"
#include "yacc.tab.h"
#include <string.h>
// belows are the same with the original
%}
plus            \+
minus           -
multiply        \*
divide          /
modulus         "mod"
greater         >
smaller         <
equal           =
and             "and"
or              "or"
not             "not"
define          "define"
fun             "fun"
if              "if"
separator       [\t\n\r ]
letter          [a-z]
digit           [0-9]
number          0|[1-9]digit*|-[1-9]digit*
ID              letter(letter|digit|-)*
bool-val        "#t"|"#f"
left_bracket    "("
right_bracket   ")"
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
{ID}            { yylval.strval = str(yytext); return ID; }
{bool-val}      {
    if(strcmp(yytext, "#t") == 0)
        yylval.bval = true;
    else if (strcmp(yytext, "#f") == 0)
        yylval.bval = false;
    return BOOL_VAL;
}
{left_bracket}  { return LEFT_BRACKET; }
{right_bracket} { return RIGHT_BRACKET; }
%%