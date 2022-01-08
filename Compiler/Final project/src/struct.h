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
    int type = 0;
    bool bval = 0;
    string strval = "";
    int ival = 0;
    string op_type = "";

    void setValue(char type, int a) {  // contain bool
        switch (type) {
            case 'i':
                this->type = 1;
                this->ival = a;
                break;
            case 'b':
                this->type = 2;
                this->bval = (bool)a;
                break;
        }
    }

    void setValue(char type, string s) {
        switch (type) {
            case 's':
                this->type = 3;
                this->strval = s;
                break;
        }
    }

    void setOP(string op) { this->op_type = op; }

    int getType() { return this->type; }

    string getOPType() { return this->op_type; }
};

struct Type_UNION {
    bool bval;
    int ival;
    string strval;
    Node *nval;
};

#define YYSTYPE Type_UNION

#endif  // !_STRUCT_HPP_
