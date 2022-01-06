#ifndef _STRUCT_HPP_
#define _STRUCT_HPP_

#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;

extern "C" {
int yylex(void);
}

struct Node {
    Node *left;
    Node *right;
};

struct Type_UNION {
};

#define YYSTYPE Type_UNION

#endif // !_STRUCT_HPP_
