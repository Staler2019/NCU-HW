%option noyywrap
%{
#include "struct.h"
#include "yacc.tab.h"
// belows are the same with the original
%}
plus            \+
minus           -
multiply        \*
divide          /
modulus         "mod"
greater         >
smaller         <
equAL           =
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

%%