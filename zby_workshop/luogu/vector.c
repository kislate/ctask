#include <stdio.h>
#include <stdlib.h>

int find(int* a, int* b, int m) {
    for (int i = 0; i < m; i++) {
        if (b[i] <= a[i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int** xl = (int**)malloc(sizeof(int*)*n);
    for (int i = 0; i < n; i++) {
        xl[i] = (int*)malloc(sizeof(int)*m);
        for (int j = 0; j < m; j++) {
            scanf("%d", &xl[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        int found = 0;
        int a = -1;
        for (int j = 0; j < n; j++) {
            if (i != j && find(xl[i], xl[j], m)) {
                if (!found) {
                    a = j;
                    found = 1;
                }
            }
        }
        if (found) {
            printf("%d\n", a+1);
        }
        else {
            printf("0\n");
        }
    }
    for (int i = 0; i < n; i++) {
        free(xl[i]);
    }
    free(xl);
    return 0;
}