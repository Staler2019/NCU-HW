%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int title_count = 1;
char str[200];

void mysubstr(const char* input, int start, int end, char* str){
    memset(str, '\0', 200);
    if(start > end || end > strlen(input)){
        return;
    }
    strncpy(str, input+start, end-start+1);
}
%}
eol                     [\n\r]
line                    ^---
pic                     !\[.*\]\(.*\);
%x TITLE
%x TITLE_BLANK
%x IMG
%x IMG_SRC
%x STARTING
%x STARTING_CHECKBOX
%x STARTING_CHECKBOX_WORD
%x LIST
%x LIST_CONTENT
%x HYPER
%x HYPER_SRC
%x QUOTE
%x QUOTE_STRONG
%%
^#                      { title_count = 1; BEGIN TITLE; }
<TITLE>[ ]              { BEGIN TITLE_BLANK; }
<TITLE>#                { title_count++; }
<TITLE_BLANK>[^\n\r]+   {
    printf("<h%d>",title_count);
    ECHO;
    printf("</h%d>\n",title_count);
    BEGIN INITIAL;
}
{line}                  { printf("<hr />\n"); }
^!\[                    { printf("<img alt=\""); BEGIN IMG; }
<IMG>[^\]]*             { ECHO; printf("\" src=\""); BEGIN IMG_SRC; }
<IMG_SRC>.              { ; }
<IMG_SRC>[^\]\(\)]*     { ECHO; printf("\">\n"); BEGIN INITIAL;}
^-                      { BEGIN STARTING; }
<STARTING>[ ]\[         { printf("<p>\n\t<input "); BEGIN STARTING_CHECKBOX; }
<STARTING_CHECKBOX>[Xx]\][ ]    { printf("checked=\"checked\" type=\"checkbox\" /> "); BEGIN STARTING_CHECKBOX_WORD; }
<STARTING_CHECKBOX>[ ]\][ ]     { printf("type=\"checkbox\" /> "); BEGIN STARTING_CHECKBOX_WORD; }
<STARTING_CHECKBOX_WORD>[^\n\r]+    { ECHO; printf("\n</p>\n"); BEGIN INITIAL; }
^\*[ ]                  { printf("<ul>\n\t<li>"); BEGIN LIST_CONTENT; }
<LIST_CONTENT>[^\n\r]*  { ECHO; printf("</li>\n"); BEGIN LIST; }
<LIST>^\*[ ]            { printf("\t<li>"); BEGIN LIST_CONTENT; }
<LIST>{eol}             { ; }
<LIST>^---              { printf("</ul>\n<hr />\n"); BEGIN INITIAL; }
^\[                     { BEGIN HYPER; }
<HYPER>[^\]]*\]\(       { mysubstr(yytext, 0, yyleng-3, str); printf("<a href=\""); BEGIN HYPER_SRC; }
<HYPER_SRC>[^\)]*       { ECHO; printf("\">\n\t<span>%s</span>\n</a>\n", str); BEGIN INITIAL; }
^>[ ]                   { printf("<blockquote>\n"); BEGIN QUOTE; }
<QUOTE>\*\*             { printf("<strong>"); BEGIN QUOTE_STRONG; }
<QUOTE_STRONG>\*\*      { printf("</strong>"); BEGIN QUOTE; }
<QUOTE_STRONG>.         { ECHO; }
<QUOTE>^>[ ]            { ; }
<QUOTE>^---             { printf("</blockquote>\n<hr />\n"); BEGIN INITIAL; }
<QUOTE>.                { ECHO; }

^{eol}                  { printf("\n"); }
{eol}                   { ; }
.                       { ; }
%%
int main(int argc, char *argv[]) {
    yylex();
    return 0;
}