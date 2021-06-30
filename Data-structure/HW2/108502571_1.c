#include <stdio.h>
#include <stdlib.h>

#define QUEUESIZE 1001

/* --- queue definition is blow --- */
typedef struct objQueue {
    int arr[QUEUESIZE]{};
    int rear = 0; // the next element will be put
    int front = 0; // the front element position
} queue;
int isEmpty(queue* q) {
    if (q->rear == q->front)
        return 1;
    else
        return 0;
}
int isFull(queue* q) {
    if ((q->rear + 1) % QUEUESIZE == q->front)
        return 1;
    else
        return 0;
}
int front(queue* q) { return q->arr[q->front]; }
int back(queue* q) { return q->arr[(q->rear + QUEUESIZE - 1) % QUEUESIZE]; }
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
    for (int i = q->front; i != q->rear && !isEmpty(q); i = (i + 1) % QUEUESIZE)
        printf("%d ", q->arr[i]);
    printf("\n*end*queue*\n");
}
/* --- my functions are above - */

/* --- Task 1 functions are blow --- */
int Add(queue* q, int n) {
    if (isFull(q)) return 0;
    q->arr[q->rear] = n;
    q->rear = (q->rear + 1) % QUEUESIZE;
    return 1;
}
int Delete(queue* q) {
    if (isEmpty(q)) return 0;
    q->front = (q->front + 1) % QUEUESIZE;
    return 1;
}
/* --- Task 1 functions are above -- */

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