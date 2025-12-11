#include <stdio.h>
int main() {
    int pq[3], num, sz = 0; char str[87];
	for (; scanf("%s %d", str, &num) != EOF; ) {
		if (str[0] == 'i') {
            pq[sz++] = num;
            if (sz >= 2 && pq[sz - 1] < pq[0]) { int t = pq[sz - 1]; pq[sz - 1] = pq[0]; pq[0] = t; }
		} else {
            if (pq[0] == num) {
                if (sz == 2) pq[0] = pq[1];
                else if (sz == 3) {
                    pq[0] = (pq[1] < pq[2]) ? pq[1] : pq[2];
                    pq[1] = (pq[1] > pq[2]) ? pq[1] : pq[2];
                }
            }
            else if (pq[1] == num) pq[1] = pq[2];
            sz--;
		}
	}
	for (int i = 0; i < sz; i++) printf("%d ", pq[i]);
}