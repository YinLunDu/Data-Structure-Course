#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
const int N = 1005;
int pos[1000];
int lc(int id) { return 2 * id + 1; }
int rc(int id) { return 2 * id + 2; }
int par(int id) { return (id - 1) / 2; }
void swap(int *x, int *y) {
	int tmp = *x;
	*x = *y;
	*y = tmp;
}
struct Priority_Queue {
	int *a;
	int sz;
};
// struct Priority_Queue *init() {
struct Priority_Queue *init() {
	struct Priority_Queue *Q = malloc(sizeof(struct Priority_Queue));
	Q->a = (int *)malloc(N * sizeof(int));
	Q->sz = 0;
	return Q;
}
int SIZE(struct Priority_Queue *Q) { return Q->sz; }
bool is_empty(struct Priority_Queue *Q) { return Q->sz == 0; }


void adjust_down(struct Priority_Queue *Q, int id) {
    while ((lc(id) < Q->sz) || (rc(id) < Q->sz)) {
		int smallest_id = id;
		if (lc(id) < Q->sz && Q->a[smallest_id] > Q->a[lc(id)])
			smallest_id = lc(id);
		if (rc(id) < Q->sz && Q->a[smallest_id] > Q->a[rc(id)])
			smallest_id = rc(id);
		if (id != smallest_id) {
			swap(&Q->a[id], &Q->a[smallest_id]);
            swap(&pos[Q->a[id]], &pos[Q->a[smallest_id]]);
			id = smallest_id;
		} else {
			break;
		}
	}
}

void adjust_up(struct Priority_Queue *Q, int id) {
    while (id > 0 && Q->a[id] < Q->a[par(id)]) {
        swap(&pos[Q->a[id]], &pos[Q->a[par(id)]]);
        swap(&Q->a[id], &Q->a[par(id)]);
        id = par(id);
    }
}

void push(struct Priority_Queue *Q, int x) {
	int id = Q->sz;
	Q->a[id] = x;
    pos[x] = id;
	Q->sz += 1;
	adjust_up(Q, id);
}


void pop(struct Priority_Queue *Q) {
	if (is_empty(Q)) return;
	swap(&Q->a[0], &Q->a[Q->sz - 1]);
    swap(&pos[Q->a[0]], &pos[Q->a[Q->sz - 1]]);
	Q->sz -= 1;
	int id = 0;
    adjust_down(Q, id);
}


int top(struct Priority_Queue *Q) {
	return Q->a[0];
}

void delete(struct Priority_Queue *Q, int x) {
    int id = pos[x];
    if (id == Q->sz - 1) {
        Q->sz -= 1;
    } else {
        Q->a[id] = Q->a[Q->sz - 1];
        pos[Q->a[id]] = id;
        Q->sz -= 1;
		adjust_up(Q, id);
		adjust_down(Q, id);
    }
}

int main() {
	struct Priority_Queue *Q = init();
	int num;
	char str[N];
	while (scanf("%s %d", &str, &num) != EOF) {
		if (str[0] == 'i')
			push(Q, num);
		else
			delete(Q, num);
	}
	for (int i = 0; i < Q->sz; i++) printf("%d ", Q->a[i]);
}