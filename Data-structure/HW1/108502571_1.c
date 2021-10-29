#include <stdio.h>

#define STACKSIZE 1000
const int LENGTH = STACKSIZE;

/* --- stack definition is blow --- */
struct objStack {
    int top;
    int item[STACKSIZE];
};
typedef struct objStack stack;
stack createStack() {
    stack st;
    st.top = 0;
    return st;
}
int empty(stack *st) {
    if (st->top) return 0;
    return 1;
}
int push(stack *st, int n) {
    if (st->top == STACKSIZE) return 0;
    st->item[st->top++] = n;
    return 1;
}
int pop(stack *st) {  // if no element, return 0
    if (empty(st)) return 0;
    return st->item[--st->top];
}
int back(stack *st) {
    if (empty(st)) return 0;
    return st->item[st->top - 1];
}
int size(stack *st) { return st->top; }
/* --- stack definition is above -- */

/* --- my functions are blow --- */
int getline(char *s, int num) {  // output size of the given string
    int g = 0;
    char c;
    if (!num) return 0;
    while (scanf("%c", &c)) {
        // printf("%c %d\n", c,g);
        if (c == '\n') break;
        if (g == num) break;
        s[g++] = c;
    }

    return g;
}
/* --- my functions are above - */

/* --- Task 1 functions are blow --- */
char *checkBalance(char *str, int size) {
    stack s = createStack();
    int unb = 0;
    for (int i = 0; i < size && !unb; i++) {
        switch (str[i]) {
            case '(':
            case '[':
            case '{':
                push(&s, str[i]);
                break;
            case ')':
                if (pop(&s) != '(') unb = 1;
                break;
            case ']':
                if (pop(&s) != '[') unb = 1;
                break;
            case '}':
                if (pop(&s) != '{') unb = 1;
                break;
        }
    }
    if (unb)
        return "Unbalanced";
    else
        return "Balanced";
}
/* --- Task 1 functions are above -- */

int main() {
    char in[LENGTH + 5];
    for (;;) {
        int size = getline(in, LENGTH);
        if (in[0] == '-' && in[1] == '1' && size == 2) break;
        printf("> %s\n\n", checkBalance(in, size));
    }
}