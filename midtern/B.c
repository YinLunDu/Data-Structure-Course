#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#define MAX_N 20
#define lc (id*2+1)
#define rc (id*2+2)

void swap(int *x, int *y) {
    int t = *x;
    *x = *y;
    *y = t;
}
int main() {
    // Input
    int n;  // The first line input
    int heap[MAX_N];  // operations should be performed on this array
    int size = 0;

    if (scanf("%d", &n) != 1) {
        return 1; 
    }

    while (scanf("%d", &heap[size]) == 1) {
        size++;
        if (size >= MAX_N) break; 
    }

    for (int i = 1; i <= n; i++) {
        int sz = size - i;
        swap(&heap[0], &heap[sz]);
        int id = 0;
        while (lc < sz || rc < sz) {
            int sid = id;
            if (lc < sz && heap[sid] < heap[lc])
                sid = lc;
            if (rc < sz && heap[sid] < heap[rc])
                sid = rc;
            if (id != sid) {
                swap(&heap[id], &heap[sid]);
                id = sid;
            } else 
                break;
        }
    }

    // Output
    for (int i = 0; i < size; i++) {
        printf("%d", heap[i]);
        if (i < size-1) printf(" ");
    }
    printf("\n");

    return 0;
}