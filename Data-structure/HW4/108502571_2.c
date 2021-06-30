#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define _TEST

typedef char* string;

void print(bool graph[][1024], int vertice);
string is_same_color(bool graph[][1024], int vertice);
bool fill_color(int color[1024], bool graph[][1024], int vertice, int starter);

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) && n != -1 && m != -1) {
        // init_bool
        bool graph[1024][1024];
        for (int i = 0; i < 1024; i++) memset(graph[i], 0, n * n);
        // input edges
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            graph[a][b] = graph[b][a] = 1;
        }
        // cal & print
        print(graph, n);
    }

    return 0;
}

void print(bool graph[][1024], int vertice) {
    printf("> %s\n", is_same_color(graph, vertice));

    for (int i = 0; i < vertice; i++) {
        printf(">");
        for (int j = 0; j < vertice; j++) printf(" %d", graph[i][j]);
        printf("\n");
    }
    // a blank between cases
    printf("\n");
    return;
}

string is_same_color(bool graph[][1024], int vertice) {
    // DEF: color: 1, -1
    int color[1024];
    memset(color, 0, vertice * sizeof(int));
    color[0] = 1;
    string ret_str = "";
    if (fill_color(color, graph, vertice, 0))
        ret_str = "Bicolorable";
    else
        ret_str = "Not bicolorable";
    return ret_str;
}

// dfs
bool fill_color(int color[1024], bool graph[][1024], int vertice, int starter) {
    for (int i = 0; i < vertice; i++) {
        bool test = true;

        if (graph[starter][i]) {
            if (color[i]) {  // if colored
                // if adjacent ones are same
                if (color[starter] == color[i])
                    return false;
                else
                    continue;
            }
            color[i] = color[starter] * (-1);
            test = fill_color(color, graph, vertice, i);
        }

        // if prev return false, then return false, too.
        if (!test) return false;
    }
    return true;
}
