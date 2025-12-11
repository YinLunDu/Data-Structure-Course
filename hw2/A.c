#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int hash_table[105][25];

signed main() {
    char s[1000];
    int n, m, x;
    scanf("%s %d", s, &n);
    scanf("%s %d", s, &m);
    for (int i = 0; i < 105; i++)
        for (int j = 0; j < 25; j++)
            hash_table[i][j] = -1;
    while (scanf("%s", s) != EOF) {
        if (s[0] == 'e') break;
        scanf("%d", &x);
        if (s[0] == 'i') {
            int i = x % n, j = 0;
            bool flag = false;
            while (true) {
                for (j = 0; j < m; j++)
                    if (hash_table[i][j] == -1) {
                        hash_table[i][j] = x;
                        flag = true;
                        break;
                    }
                if (flag) break;
                i = (i + 1) % n;
            }
        } else if (s[0] == 'd') {
            int i = x % n, j = 0;
            bool flag = false;
            while (true) {
                for (j = 0; j < m; j++)
                    if (hash_table[i][j] == x) {
                        hash_table[i][j] = -1;
                        flag = true;
                        break;
                    }
                if (flag) break;
                i = (i + 1) % n;
            }
        } else {
            int i = x % n, j = 0;
            bool flag = false;
            while (true) {
                for (j = 0; j < m; j++)
                    if (hash_table[i][j] == x) {
                        flag = true;
                        break;
                    }
                if (flag) break;
                i = (i + 1) % n;
            }
            printf("%d %d\n", i, j);
        }
    }
}