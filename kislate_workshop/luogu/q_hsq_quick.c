#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASH_SIZE 220000

typedef struct HashNode {
    char key[20];
    struct HashNode *next;
} HashNode;

unsigned int hash(const char *str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % HASH_SIZE;
}

void insert(HashNode **hashTable, const char *str) {
    unsigned int index = hash(str);
    HashNode *newNode = (HashNode *)malloc(sizeof(HashNode));
    strcpy(newNode->key, str);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

int search(HashNode **hashTable, const char *str) {
    unsigned int index = hash(str);
    HashNode *node = hashTable[index];
    while (node) {
        if (strcmp(node->key, str) == 0) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}

void freeHashTable(HashNode **hashTable) {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *node = hashTable[i];
        while (node) {
            HashNode *temp = node;
            node = node->next;
            free(temp);
        }
    }
}
void quicksort(char a[][20], int low, int high);
int partition(char a[][20], int low, int high);
int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    char old[110000][20]; // n
    int flag[110000]; // n
    char full[110000][20]; // m
    char new1[110000][20]; // k
    HashNode *hashTable[HASH_SIZE] = {0};

    for (int i = 0; i < n; i++) {
        scanf("%s", old[i]);
        flag[i] = 0; // 0为要输出
    }
    for (int i = 0; i < m; i++) {
        scanf("%s", full[i]);
        insert(hashTable, full[i]);
    }
    for (int i = 0; i < k; i++) {
        scanf("%s", new1[i]);
    }
    for (int i = 0; i < n; i++) {
        if (search(hashTable, old[i])) {
            flag[i] = 1;
        }
    }
    char putout[210000][20];
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (flag[i] == 0) {
            strcpy(putout[j], old[i]);
            j++;
        }
    }
    for (int i = 0; i < k; i++) {
        strcpy(putout[j], new1[i]);
        j++;
    }
    quicksort(putout, 0, j - 1);
    for (int i = 0; i < j; i++) {
        puts(putout[i]);
    }

    freeHashTable(hashTable);
}

void quicksort(char a[][20], int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);
        quicksort(a, low, pi - 1);
        quicksort(a, pi + 1, high);
    }
}

int partition(char a[][20], int low, int high) {
    char pivot[20];
    strcpy(pivot, a[high]);
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (strcmp(a[j], pivot) < 0) {
            i++;
            char temp[20];
            strcpy(temp, a[i]);
            strcpy(a[i], a[j]);
            strcpy(a[j], temp);
        }
    }
    char temp[20];
    strcpy(temp, a[i + 1]);
    strcpy(a[i + 1], a[high]);
    strcpy(a[high], temp);
    return (i + 1);
}