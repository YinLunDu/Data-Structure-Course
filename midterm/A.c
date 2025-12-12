#include <stdio.h> 
#include <stdlib.h>
#define MAX_NODES 20

int dsu[MAX_NODES];

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
    scanf("%d", &n);  // Read the number of nodes
    
    // Read adjacency matrix
    int matrix[MAX_NODES][MAX_NODES];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    for (int i = 0; i < n; i++) dsu[i] = i;
    
    int totalCost = 0;      // Storing the total cost of the minimum spanning tree
    int mst[MAX_NODES][2];  // Store the edges of the minimum spanning tree. 
                            // If the i-th edge is (u, v), then mst[i-1][0] = u,mst[i-1][1] = v


    for (int T = 0; T < n - 1; T++) {
        int mx = 100000000, v = 0, u = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] < mx && matrix[i][j] != 0 && find(i) != find(j)) {
                    mx = matrix[i][j];
                    v = i; u = j;
                }
            }
        mst[T][0] = v; mst[T][1] = u;
        merge(v, u);
        totalCost += mx;
    }

    // OutPut
    printf("%d", totalCost);
    for (int i = 0; i < n-1; i++) {
        printf(",(%d,%d)", mst[i][0], mst[i][1]);  
    }
    printf("\n");
    
    return 0;
}