%{
    int tabCount = 0;
%}
upperTab    \{
lowerTab    \}
line        [^ \n\r\{\}][^\n\r\{\}]+
eol         \n
line_u      {line}\{[\r\n\{\}]*
line_l      {line}\}[\r\n\{\}]*
%%
{upperTab}  {
    printf("\t");
    ECHO;
    tabCount++;
    // printf("__upper__%d", tabCount);
}
{lowerTab}  {
    ECHO;
    tabCount--;
    // printf("__lower__%d", tabCount);
}
{line}      {
    if (tabCount > 0)
        printf("\t");
    ECHO;
    // printf("__line__%d", tabCount);
}
{eol}       {
    ECHO;
    for (int i = 0; i < tabCount - 1; i++)
        printf("\t");
    // printf("__eol__%d", tabCount);
}
{line_u}    {
    if (tabCount > 0)
        printf("\t");
    ECHO;
    tabCount++;
    // printf("__line_u__%d", tabCount);
}
{line_l}    {
    if (tabCount > 0)
        printf("\t");
    ECHO;
    tabCount--;
    // printf("__line_l__%d", tabCount);
}
.           { ; }
%%
int main(int argc, char *argv[]) {
    yylex();
    return 0;
    // 撞牆期過不去，你不是第一位，也不是最後一位，但如果你要找飯吃，風波一過很快就被刷掉了
}