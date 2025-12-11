#include <stdio.h>
#define MAX_N 20

int dsu[20];

int find(int x) {
    if (x == dsu[x]) return x;
    return dsu[x] = find(dsu[x]);
}

void merge(int x, int y) {
    x = find(x); y = find(y);
    dsu[y] = x;
}

int main() {
    // Input
    int n;
    int cycle_x = -1, cycle_y = -1;     // The edge (x, y) used to determine whether there is a cycle, x < y
    int has_cycle = 0;      // Used to determine whether there is a cycle
    
    // Read the number of nodes
    scanf("%d", &n);

    int graph[n][n];
    
    // Read adjacency matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    for (int i = 0; i < n; i++) dsu[i] = i;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (has_cycle == 1) continue;
            if (graph[i][j] == 1) {
                if (find(i) == find(j)) {
                    has_cycle = 1;
                    cycle_x = i;
                    cycle_y = j;
                }
                merge(i, j);
                cycle_x = i;
                cycle_y = j;
            }
        }
    }

    // Output
    if(has_cycle) {
        printf("True,(%d,%d)\n", cycle_x, cycle_y);
    } else {
        printf("False,(%d,%d)\n", cycle_x, cycle_y);
    }
    
    
    return 0;
}