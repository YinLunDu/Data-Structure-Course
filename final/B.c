#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000
// SMMH structure
typedef struct {
    int heap[MAX_SIZE];
    int size;
} SMMH;

// Initialize SMMH
void initialize(SMMH* smmh) {
    smmh->size = 0;
    memset(smmh->heap, 0, sizeof(smmh->heap)); 
}

// Swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Helper function to maintain SMMH property after insertion
void bubbleUp(SMMH* smmh, int index) {
    if (index % 2 == 1){
        if (smmh->heap[index-1] > smmh->heap[index]){
            swap(&smmh->heap[index], &smmh->heap[index-1]);
            index = index - 1; 
        }
    }
    

    int parent = index / 2;
    if (parent==1) return;

    if (index % 4 < 2) { 
        if (smmh->heap[index] > smmh->heap[parent + 1]) {
            swap(&smmh->heap[index], &smmh->heap[parent + 1]);
            bubbleUp(smmh, parent + 1);
        }
        if (smmh->heap[index] < smmh->heap[parent]) {
            swap(&smmh->heap[index], &smmh->heap[parent]);
            bubbleUp(smmh, parent);
        }
    } else { 
        if (smmh->heap[index] > smmh->heap[parent]) {
            swap(&smmh->heap[index], &smmh->heap[parent]);
            bubbleUp(smmh, parent);
        }
        if (smmh->heap[index] < smmh->heap[parent - 1]) {
            swap(&smmh->heap[index], &smmh->heap[parent - 1]);
            bubbleUp(smmh, parent - 1);
        }
    }
}

// Insert a key into SMMH
void insert(SMMH* smmh, int key) {
    if (smmh->size >= MAX_SIZE - 1) return;
    
    smmh->size++;
    smmh->heap[smmh->size+1] = key;
    bubbleUp(smmh, smmh->size + 1);
}

int lc(int x) { return x * 2; }
int rc(int x) { return x * 2 + 1; }

void down(SMMH* smmh, int x) {
    int sib = 0;
    if (x % 2) {
        sib = x - 1;
        if (smmh->heap[x] < smmh->heap[sib])
            swap(&smmh->heap[x], &smmh->heap[sib]);
    } else {
        sib = x + 1;
        if (sib <= smmh->size + 1 && smmh->heap[x] > smmh->heap[sib])
            swap(&smmh->heap[x], &smmh->heap[sib]);
    }
    int gc = smmh->heap[x], id = 0;
    if (x % 2 == 0) {
        if (lc(sib) <= smmh->size + 1 && smmh->heap[lc(sib)] < gc) {
            gc = smmh->heap[lc(sib)];
            id = lc(sib);
        }
        if (lc(x) <= smmh->size + 1 && smmh->heap[lc(x)] < gc) {
            gc = smmh->heap[lc(x)];
            id = lc(x);
        }
    } else {
        if (rc(sib) <= smmh->size + 1 && smmh->heap[rc(sib)] > gc) {
            gc = smmh->heap[rc(sib)];
            id = rc(sib);
        }
        if (rc(x) <= smmh->size + 1 && smmh->heap[rc(x)] > gc) {
            gc = smmh->heap[rc(x)];
            id = rc(x);
        }
    }
    if (id) {
        swap(&smmh->heap[x], &smmh->heap[id]);
        down(smmh, id);
    }
}

//Write a function to delete the maximum and minimum values
void deleteMin(SMMH* smmh){
    // Your answer
    if (smmh->size + 1 > 2) smmh->heap[2] = smmh->heap[smmh->size + 1];
    smmh->size--;
    down(smmh, 2);
}
void deleteMax(SMMH* smmh){
    // Your answer 
    if (smmh->size + 1 > 3) smmh->heap[3] = smmh->heap[smmh->size + 1];
    smmh->size--;
    down(smmh, 3);
}

void printLevelOrder(SMMH* smmh) {
    if (smmh->size == 0 ) {
        printf("\n");
        return;
    }
    for (int i = 2; i <= smmh->size+1; i++) {
        printf("%d", smmh->heap[i]);
        if (i < smmh->size + 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    SMMH smmh;
    initialize(&smmh);
    
    char command[20];
    int key;

    while (1) {
        scanf("%s", command);
        if (strcmp(command, "exit") == 0) {
            printLevelOrder(&smmh);
            break;
        } else if (strcmp(command, "insert") == 0) {
            scanf("%d", &key);
            insert(&smmh, key);
        } else if (strcmp(command, "delete-min") == 0) {
            deleteMin(&smmh);
        } else if (strcmp(command, "delete-max") == 0) {
            deleteMax(&smmh);
        }  
    } return 0;
}