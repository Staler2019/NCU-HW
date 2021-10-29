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
/*thinks:
因為他只需要算出the length of the ciphertext after
coding，所以我們只要得知每個字元的level即可
*/

// root node will be emplace in Linked_priorityQueue
struct nodeObj {
    int data;
    struct nodeObj *left;
    struct nodeObj *right;
};
typedef struct nodeObj Node;

Node *createNode(int n = NULL) {
    getmem(Node, no);
    no->data = n;
    no->left = NULL;
    no->right = NULL;
    return no;
}
Node *createNode(Node *leftNode, Node *rightNode) {
    getmem(Node, no);
    no->data = leftNode->data + rightNode->data;
    no->left = leftNode;
    no->right = rightNode;
    return no;
}
/*
create a linked_list to remember the nodes remained in this tree
*/
// the first is an empty Linked_priorityQueue
struct node_linked_priority_queueObj {
    Node *data;
    struct node_linked_priority_queueObj *prev;
    struct node_linked_priority_queueObj *next;
};
typedef struct node_linked_priority_queueObj Linked_priorityQueue;

Linked_priorityQueue *createLinked_priorityQueue() {
    getmem(Linked_priorityQueue, pq);
    pq->data = NULL;
    pq->prev = NULL;
    pq->next = NULL;
    return pq;
}
void push(Linked_priorityQueue *pq, Node *n) {
    Linked_priorityQueue *last = pq;
    while (last->next != NULL) last = last->next;

    Linked_priorityQueue *put = createLinked_priorityQueue();
    last->next = put;
    put->data = n;
    put->prev = last;
}
Node *pop(Linked_priorityQueue *pq) {
    Linked_priorityQueue *target = pq->next;
    Linked_priorityQueue *last = target;

    if (target == NULL) {
        printf("Linked_priorityQueue is empty\n");
        return createNode();
    }
    while (last->next != NULL) {
        last = last->next;
        target = (target->data->data > last->data->data) ? last : target;
    }
    Node *ans = target->data;

    target->prev->next = target->next;
    if (target->next != NULL) target->next->prev = target->prev;
    free(target);
    return ans;
}

void printQueue(Linked_priorityQueue *pq) {
    Linked_priorityQueue *last = pq->next;
    while (last != NULL) {
        print(last->data->data);
        last = last->next;
    }
}
void printCH(int *ch) {
    for (int i = 0; i < 52; i++) printf("%d ", ch[i]);
    printf("\n");
}
int dfs(Node *root, int level) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return root->data * level;

    int ans = dfs(root->left, level + 1) + dfs(root->right, level + 1);
    return ans;
}
int main() {
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    while (true) {
        // input
        int ch[52];
        char str[SIZE]{};
        int length = getline(str, SIZE);
        if (!strcmp(str, "-1"))  // strings equal
            return 0;
        for (int i = 0; i < 52; i++) ch[i] = 0;
        for (int i = 0; i < length; i++) {
            char c = str[i];
            if (c >= 'A' && c <= 'Z')
                ch[c - 'A']++;
            else if (c >= 'a' && c <= 'z')
                ch[c - 'a' + 26]++;
        }

        // create tree
        Linked_priorityQueue *pq = createLinked_priorityQueue();
        int queueSize = 0;
        for (int i = 0; i < 52; i++) {
            if (ch[i] != 0) {
                push(pq, createNode(ch[i]));
                queueSize++;
            }
        }
        // printQueue(pq);
        while (queueSize > 1) {
            Node *left = pop(pq);
            Node *right = pop(pq);
            Node *root = createNode(left, right);
            push(pq, root);
            queueSize--;
        }

        // dfs
        Node *root = pop(pq);
        int ans = dfs(root, 0);
        print(ans);
    }
}