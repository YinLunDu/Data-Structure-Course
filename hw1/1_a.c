#include <stdio.h>
#include <stdbool.h>
const int N = 1005;
struct Stack {
    int top, sz;
    int *a;
};
struct Stack* build() {
	struct Stack* s = (struct Stack*)malloc(sizeof(struct Stack));
	s->top = s->sz = 0;
	s->a = (int *)malloc(N * sizeof(int));
	return s;
}
bool is_empty(struct Stack* s) {
	return (s->sz == 0);
}
void push(struct Stack* s, int val) {
    s->a[s->top] = val;
    s->top += 1;
	s->sz += 1;
}
void pop(struct Stack* s) {
    s->top -= 1;
	s->sz -= 1;
}
int top(struct Stack* s) {
	return s->a[s->top - 1];
}
int SIZE(struct Stack* s) {
	return s->sz;
}
/*
1: +
2: -
3: *
4: /
 */
char tran_ch(int x) {
    if (x == 1) return '+';
    if (x == 2) return '-';
    if (x == 3) return '*';
    if (x == 4) return '/';
}

int tran_int(char c) {
    if (c == '+') return 1;
    if (c == '-') return 2;
    if (c == '*') return 3;
    if (c == '/') return 4;
}

int main() {
    char s[N];
    scanf("%s", &s);
    struct Stack *op = build();
    
    char ans[N]; int id = 0;
    bool NextIsNumber = true;
    for (int i = 0; i < (int)strlen(s); i++) {
        if ((s[i] == '+') || (s[i] == '-') || (s[i] == '*') || (s[i] == '/'))
            push(op, tran_int(s[i]));
        else if (('a' <= s[i] && s[i] <= 'z') || ('A' <= s[i] && s[i] <= 'Z')) {
            ans[id] = s[i];
            id += 1;
            NextIsNumber = false;
        }
        if (NextIsNumber == false && is_empty(op) == false) {
            int x = top(op); pop(op);
            ans[id] = tran_ch(x);
            id += 1;
            NextIsNumber = true;
        }
    }
    for (int i = 0; i < id; i++)
        printf("%c", ans[i]);
}