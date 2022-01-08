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
    Node *parent;
    string type;
    void *value;

    Node(Node *left, Node *right, Node *parent) {
        left = left;
        right = right;
        parent = parent;
    };
};

struct Type_UNION {
    bool bval;
    int ival;
    string strval;
    Node *nval;
};

#define YYSTYPE Type_UNION

#endif  // !_STRUCT_HPP_
