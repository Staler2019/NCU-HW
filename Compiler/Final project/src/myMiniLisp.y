%{
// struct settings
#include "struct.h"
extern "C"{
    void yyerror(const char* message) {
        // printf("syntax error\n");
        cout << message << endl;
    };
}

// my code
#define elif else if
#define notNullptrGoCal(n)      \
            if(n != nullptr) {  \
                cal(n);         \
            }
// fun
Node *createNptr(Node *left, Node *right) {
    Node *n = (Node *)malloc(sizeof(Node *));
    n->left = left;
    n->right = right;
    n->type = 0;
    n->bval = 0;
    // n->strval = "";
    // cerr << "success" << endl;
    n->ival = 0;
    // n->op_type = "";
    return n;
}

void nodeConstructError() {
    cerr << "node construction error" << endl;
    exit(0);
}


int cal(Node *now) {
    int type = now->getType();
    int left, right;
    switch (type) {
        case 0: {  // operator
            string opType = now->getOPType();
            if (opType == "") nodeConstructError();

            if (opType == "pn") {  // print number
                left = cal(now->left);
                cout << left << endl;
                notNullptrGoCal(now->right);
            }
            elif (opType == "pb") {  // print bool
                bool left = (bool)(cal(now->left));
                cout << ((left) ? "#t" : "#f") << endl;
                notNullptrGoCal(now->right);
            }

            left = cal(now->left);
            right = cal(now->right);
            if (opType == "+") {
                return left + right;
            }
            elif (opType == "-") { return left - right; }
            elif (opType == "*") { return left * right; }
            elif (opType == "/") { return left / right; }

            break;
        }
        case 1: {  // int
            return now->ival;
            break;
        }
        case 2:  // bool //TODO. not ready
            return now->bval;
            break;
        case 3: // string
            break;
        default: {
            nodeConstructError();
            break;
        }
    }

    return 0;  // todo.
}

void printNode(Node *n, int dense){
    string pre = "";
    for(int i = 0; i < dense; i++){
        pre += "\t";
    }
    cerr << pre << n->getType() << " ";
    if(!n->getType()) cerr << n->getOPType();
    cerr << endl;
    if(n->left!=nullptr)
        printNode(n->left, dense+1);
    if(n->right!=nullptr)
        printNode(n->right, dense+1);
    // if(n->type) cout << n->type << endl;

}

// var
Node* root;
vector<Node*> fun_table;

// belows are the same with the original
/* my naming rule:
nonterminals    : nonterminal+
nonterminal_s   : nonterminal*
*/
%}
%token  <ival>      NUMBER
%token  <bval>      BOOL_VAL
%token  <strval>    ID
%token  PLUS MINUS MULTIPLY DIVIDE MODULUS GREATER SMALLER EQUAL AND OR NOT DEFINE FUN IF LEFT_BRACKET RIGHT_BRACKET PRINT_NUM PRINT_BOOL
%type   <nval>      program stmts stmt exp def_stmt print_stmt num_op fun_exp fun_ids fun_body fun_name fun_call
%type   <nval>      variable id_s exps param_s param
%type   <nval>      plus minus multiply divide modulus greater smaller equal if_exp test_exp than_exp else_exp logical_op and_op or_op not_op
%%
program:
    stmts {
        root = $1;
    }
    ;
stmts:
    stmt stmts {
        $$ = createNptr($1, $2);
        $$->setOP("stmt");
    }
    | { $$ = nullptr; }
    ;
stmt:
    exp {
        $$ = $1;
    }
    | def_stmt {
        $$ = $1;
    }
    | print_stmt {
        $$ = $1;
    }
    ;
print_stmt:
    LEFT_BRACKET PRINT_NUM exp RIGHT_BRACKET {
        $$ = createNptr($3, nullptr);
        $$->setOP("pn");
        // cerr << "setup number" << $1 << endl;
    }
    | LEFT_BRACKET PRINT_BOOL exp RIGHT_BRACKET {
        $$ = createNptr($3, nullptr);
        $$->setOP("pb");
    }
    ;
exp:
    BOOL_VAL {
        $$ = createNptr(nullptr, nullptr);
        $$->setValue('b', $1);
    }
    | NUMBER {
        $$ = createNptr(nullptr, nullptr);
        // cerr << "setup number" << $1 << endl;
        $$->setValue('i', $1);
    }
    | variable
    | num_op
    | logical_op
    | fun_exp
    | fun_call
    | if_exp
    ;
num_op:
    plus
    | minus
    | multiply
    | divide
    | modulus
    | greater
    | smaller
    | equal
    ;
plus:
    LEFT_BRACKET PLUS exp exps RIGHT_BRACKET {

    }
    ;
minus:
    LEFT_BRACKET MINUS exp exp RIGHT_BRACKET
    ;
multiply:
    LEFT_BRACKET MULTIPLY exp exps RIGHT_BRACKET
    ;
divide:
    LEFT_BRACKET DIVIDE exp exp RIGHT_BRACKET
    ;
modulus:
    LEFT_BRACKET MODULUS exp exp RIGHT_BRACKET
    ;
greater:
    LEFT_BRACKET GREATER exp exp RIGHT_BRACKET
    ;
smaller:
    LEFT_BRACKET SMALLER exp exp RIGHT_BRACKET
    ;
equal:
    LEFT_BRACKET EQUAL exp exps RIGHT_BRACKET
    ;
exps:
    exp exps
    |
    ;
logical_op:
    and_op
    | or_op
    | not_op
    ;
and_op:
    LEFT_BRACKET AND exp exps RIGHT_BRACKET
    ;
or_op:
    LEFT_BRACKET OR exp exps RIGHT_BRACKET
    ;
not_op:
    LEFT_BRACKET NOT exp RIGHT_BRACKET
    ;
def_stmt:
    LEFT_BRACKET DEFINE variable exp RIGHT_BRACKET
    ;
variable:
    ID
    ;
fun_exp:
    LEFT_BRACKET FUN fun_ids fun_body RIGHT_BRACKET
    ;
fun_ids:
    LEFT_BRACKET id_s RIGHT_BRACKET
    ;
fun_body:
    exp
    ;
id_s:
    ID id_s
    |
    ;
fun_call:
    LEFT_BRACKET fun_exp param_s RIGHT_BRACKET
    | LEFT_BRACKET fun_name param_s RIGHT_BRACKET
    ;
fun_name:
    ID
    ;
param_s:
    param param_s
    |
    ;
param:
    exp
    ;
if_exp:
    LEFT_BRACKET IF test_exp than_exp else_exp RIGHT_BRACKET
    ;
test_exp:
    exp
    ;
than_exp:
    exp
    ;
else_exp:
    exp
    ;
%%
int main(){
    yyparse();

    printNode(root,0);
    cal(root);

    return 0;
}