#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- my functions are blow --- */
int getline(char *s, int num) {  // output size of the given string
    int size = 0;
    char c;
    if (!num) return 0;
    while (scanf("%c", &c)) {
        // printf("%c %d\n", c,g);
        if (c == '\n') break;
        if (size == num) break;
        s[size++] = c;
    }

    return size;
}
void print(int n) { printf("> %d\n", n); }
#define getmem(type, name) type *name = (type *)malloc(sizeof(type))
/* --- my functions are above - */
#define SIZE 1000


int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    while (true) {
        // input
        int length = getline(str, SIZE);
        if (!strcmp(str, "-1"))  // strings equal
            return 0;

    }
}