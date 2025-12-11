#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY -1    // Marker for an empty slot

int *hashTable;     // Dynamically allocated hash table
int n;              // Number of buckets

//Write a function to insert the values and shiftFoldingHash
int shiftFoldingHash(int key) {
    // Your answer
    char str[100];
    int i = 0;
    while (key > 0) {
        str[i] = ('0' + (key % 10));
        key /= 10;
        i++;
    }
    int sz = i;
    int res = 0;
    for (int j = sz - 1; j >= 0; j--) {
        int tmp = (str[j] - '0');
        if (j > 0) {
            j--;
            tmp = tmp * 10 + (str[j] - '0');
        }
        if (j > 0) {
            j--;
            tmp = tmp * 10 + (str[j] - '0');
        }
        res = (res + tmp) % n;
    }
    return res;
}


void insertKey(int key) {
    // Your answer
    int h = shiftFoldingHash(key);
    int i = 0;
    while (i < n) {
        int pos = (h + i*i) % n;
        // Found the key
        if (hashTable[pos] == EMPTY) {
            hashTable[pos] = key;
            return;
        }
        i++;
    }
}


void searchKey(int key) {
    int h = shiftFoldingHash(key);
    int i = 0;
    while (i < n) {
        int pos = (h + i*i) % n;
        // Found the key
        if (hashTable[pos] == key) {
            printf("%d\n", pos);
            return;
        }
        i++;
    }
}


void deleteKey(int key) {
    int h = shiftFoldingHash(key);
    int i = 0;
    while (i < n) {
        int pos = (h + i*i) % n;
        if (hashTable[pos] == key) {
            hashTable[pos] = EMPTY;
            return;
        }
        i++;
    }
}

int main() {
    scanf("bucket %d", &n);

    // Allocate the hash table
    hashTable = (int*)malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++) {
        hashTable[i] = EMPTY;  // Initialize to empty
    }

    // Read commands
    while (1) {
        char cmd[16];
        if (scanf("%s", cmd) != 1) break;

        if (strcmp(cmd, "exit") == 0) {
            break;
        } else if (strcmp(cmd, "insert") == 0) {
            int key;
            scanf("%d", &key);
            insertKey(key);
        } else if (strcmp(cmd, "delete") == 0) {
            int key;
            scanf("%d", &key);
            deleteKey(key);
        } else if (strcmp(cmd, "search") == 0) {
            int key;
            scanf("%d", &key);
            searchKey(key);
        }
    }

    free(hashTable);
    return 0;
}