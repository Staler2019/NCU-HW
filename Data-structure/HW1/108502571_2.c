#include <math.h>
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

/* --- Task 2 functions are blow --- */
int priority(char c) {
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}
int in2post(char *in, int size, char *post) {  // TODO:what is "s" means?
    stack s = createStack();
    // , post = createStack();
    int p_size = 0;
    for (int i = 0; i < size; i++) {
        switch (in[i]) {
            case '(':
                push(&s, in[i]);
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                while (priority(back(&s)) >= priority(in[i]))
                    post[p_size++] = pop(&s);
                // push(&post, pop(&s));
                push(&s, in[i]);
                break;
            case ')':  // we also take out '(', ')' in this step
                while (back(&s) != '(') post[p_size++] = pop(&s);
                // push(&post, pop(&s));
                pop(&s);  // pop out '('
                break;
            default:
                post[p_size++] = in[i];
                // push(&post, in[i]);
                break;
        }
    }
    while (!empty(&s)) post[p_size++] = pop(&s);
    // push(&post, pop(&s));
    return p_size;
}
void printString(char *s, int size) {
    printf("> ");
    for (int i = 0; i < size; i++) printf("%c ", s[i]);
    printf("\n");
}
int countPost(char *post, int p_size) {
    stack num = createStack();
    for (int i = 0; i < p_size; i++) {
        if (post[i] >= '0' && post[i] <= '9') {
            push(&num, post[i] - '0');
            continue;
        }
        int second = pop(&num), first = pop(&num);
        switch (post[i]) {
            case '+':
                push(&num, first + second);
                break;
            case '-':
                push(&num, first - second);
                break;
            case '*':
                push(&num, first * second);
                break;
            case '/':
                push(&num, first / second);
                break;
            case '^':
                push(&num, (int)pow(first, second));
                break;
            default:
                return -1;
        }
    }
    return pop(&num);
}
/* --- Task 2 functions are above -- */

int main() {
    char in[LENGTH + 5];
    for (;;) {
        int size = getline(in, LENGTH);
        if (in[0] == '-' && in[1] == '1' && size == 2) break;

        char post[LENGTH + 5];
        int post_size = in2post(in, size, post);
        printString(post, post_size);
        printf("> %d\n\n", countPost(post, post_size));
    }
}