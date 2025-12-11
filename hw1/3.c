#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
const int N = 1000;
struct Queue {
    int front, rear, sz;
    int a[1000];
};
struct Queue* build() {
	struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
	q->front = q->rear = q->sz = 0;
	return q;
}
bool is_empty(struct Queue* q) {
	return (q->front == q->rear); // (q->sz == 0)
}
void push(struct Queue* q, int val) {
    q->a[q->rear] = val;
    q->rear = (q->rear + 1) % N;
	q->sz += 1;
}
void pop(struct Queue* q) {
    q->front = (q->front + 1) % N;
	q->sz -= 1;
}
int front(struct Queue* q) {
	return q->a[q->front];
}
int SIZE(struct Queue* q) {
	return q->sz;
}
int main() {
    int n;
    scanf("%d", &n);

    struct Queue *Q = build();
    int **edge;
    edge = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) edge[i] = malloc(n * sizeof(int));
    bool *vis;
    vis = malloc(n * sizeof(bool));
    for (int i = 0; i < n; i++) vis[i] = false;
    int *ans;
    ans = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &edge[i][j]);

    int id = 0;
    vis[0] = true;
    push(Q, 0);
    while (! is_empty(Q)) {
        int v = front(Q); pop(Q);
        ans[id] = v; id += 1;
        for (int u = 0; u < n; u++) {
            if (edge[v][u] && ! vis[u]) {
                push(Q, u);
                vis[u] = true;
            }
        }
    }
    for (int i = 0; i < id; i++) printf("%d ", ans[i] + 1);
}