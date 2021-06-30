#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct listObj {
    int number;
    struct listObj* next;
};
typedef struct listObj ListNode;

void print();
void add(ListNode* pointer, int node);
void water_flow(ListNode LN[], int n, int m);

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) && n != -1 && m != -1) {
        // init adj_header: (number: n)
        ListNode adj[1024];
        for (int i = 0; i < m; i++) {
            adj[i].number = 0;
            adj[i].next = NULL;
        }

        // establish adj_list
        // TODO
        for (int j = 0; j < m; j++) {
            int input;
            scanf("%d", &input);
            if (input) {
                adj[j].number = 1;
                break;
            }
        }
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < m; j++) {
                int input;
                scanf("%d", &input);
                // make adjacency_list
                if (input) add(adj[j], i);
            }
        }

        // cal
        water_flow(adj, n, m);

        // print
        print(adj, n, m);
    }

    return 0;
}

void print(ListNode* LN, int n, int m) {
    for (int i = 0; i < n;i++){
        printf(">");
        // TODO
        for (int j = 0; j < m; j++) printf(" %d", );
    }
    return;
}

void add(ListNode* pointer, int node) {
    while (pointer->next != NULL) pointer = pointer->next;
    pointer->next = (ListNode*)malloc(sizeof(ListNode));
    pointer->number = 1;
    pointer->next->next = NULL;
    return;
}

void water_flow(ListNode LN[], int n, int m) {
    for (int i = 0; i < m; i++) {
        if (adj) }
}
