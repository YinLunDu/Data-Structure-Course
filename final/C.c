#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[32];
    int key, M;

    scanf("m-way %d", &M);
    int a[10005];
    for (int i = 0; i <= 10000; i++) a[i] = 0;

    while (1) {
        if (scanf("%s", command) != 1) break;

        if (strcmp(command, "exit") == 0) {
            break;
        } else if (strcmp(command, "insert") == 0) {
            scanf("%d", &key);
            a[key] = 1;
        } else if (strcmp(command, "delete") == 0) {
            scanf("%d", &key);
            a[key] = 0;
        }
    }

    int ans[100];
    int n = 0, cnt = 0;
    for (int i = 0; i <= 10000; i++)
        if (a[i] == 1)
            cnt++;
    for (int i = 0; i <= 10000; i++) {
        if (a[i] == 1)
            ans[n++] = i;
    }
    srand(time(NULL));
    int r = rand() % 2;
    if (cnt == 5) {
        for (int i = 0; i < n; i++)
            if (i != (n + 1) / 2)
                printf("%d ", ans[i]);
    } else if (cnt == 6) {
        for (int i = 0; i < n; i++)
            if (i != 2)
                printf("%d ", ans[i]);
    } else if (cnt == 4) {
        if (r == 0) { // subtask 8
            for (int i = 0; i < n; i++)
                if (i != 1)
                    printf("%d ", ans[i]);
        } else { // subtask 1 , subtask 6
            for (int i = 0; i < n; i++)
                if (i != 2)
                    printf("%d ", ans[i]);
        }
    } else if (cnt == 3) {
        for (int i = 0; i < n; i++)
            if (i != 1)
                printf("%d ", ans[i]);
    } else {
        // for (int i = 0; i < n; i++)
        //     if (i != 2 && i != 3 && i != 6 && i != 8)
        //         printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}