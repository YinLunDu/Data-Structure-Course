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

int get_prior(int x) {
    if (x == 1 || x == 2) return 1;
    if (x == 3 || x == 4) return 2;
}

int main() {
    char s[N];
    scanf("%s", &s);
    struct Stack *stk = build();
    
    char ans[N]; int id = 0;
    for (int i = 0; i < (int)strlen(s); i++) {
        if (('a' <= s[i] && s[i] <= 'z') || ('A' <= s[i] && s[i] <= 'Z')) {
            ans[id] = s[i];
            id += 1;
        } else {
            while (! is_empty(stk) && get_prior(top(stk)) >= get_prior(tran_int(s[i]))) {
                ans[id] = tran_ch(top(stk)); pop(stk);
                id += 1;
            }
            push(stk, tran_int(s[i]));
        }
    }
    while (! is_empty(stk)) {
        ans[id] = tran_ch(top(stk)); pop(stk);
        id += 1;
    }
    for (int i = 0; i < id; i++)
        printf("%c", ans[i]);
}