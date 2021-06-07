#include <stdio.h>
#include <stdlib.h>

/* --- queue definition is blow --- */
typedef struct node {
    int data;
    node* next;
} node;
typedef struct objQueue {
    int size = 0;
    node* front;
    node* rear;
} queue;
node* createNode() {
    node* point = (node*)malloc(sizeof(node));
    point->data = 0;
    point->next = NULL;
    return point;
}
int isEmpty(queue* q) {
    if (q->size == 0)
        return 1;
    else
        return 0;
}
int front(queue* q) { return q->front->data; }
int back(queue* q) { return q->rear->data; }
/* --- queue definition is above -- */

/* --- my functions are blow --- */
int getline(char* s, int num) {  // output size of the given string
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
void printQueue(queue* q) {
    printf("***queue***\n");
    node* point = q->front;
    while (point->next != NULL) {
        printf("%d ", point->data);
        point = point->next;
    }
    printf("\n*end*queue*\n");
}
/* --- my functions are above - */

/* --- Task 2 functions are blow --- */
int Add(queue* q, int n) {
    node* point = createNode();
    point->data = n;

    if (q->size == 0) q->front = point;

    q->rear->next = point;
    q->rear = point;
    q->size++;
    return 1;
}
int Delete(queue* q) {
    if (isEmpty(q)) return 0;
    node* point = q->front;
    q->front = q->front->next;
    free(point);
    q->size--;
    return 1;
}
/* --- Task 2 functions are above -- */

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    queue q;
    while (scanf("%d", &n)) {
        switch (n) {
            case 1:
                int input;
                scanf("%d", &input);
                Add(&q, input);
                break;
            case 2:
                if (isEmpty(&q))
                    print(-2);
                else
                    print(front(&q));
                break;
            case 3:
                if (isEmpty(&q))
                    print(-3);
                else
                    Delete(&q);
                break;
            case -1:
                return 0;
            default:
                break;
        }
        // printQueue(&q);
    }
    return 0;
}