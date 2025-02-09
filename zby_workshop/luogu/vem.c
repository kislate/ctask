#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    int* H = (int*)malloc(sizeof(int)*k);
    for (int i = 0; i < k; i++) {
        scanf("%d",H+i);
    }

    qsort(H, k, sizeof(int), compare);

    int current_layer = 1; 
    int current_num = 0;

    for (int i = 0; i < k; i++) {
        if (H[i] < current_layer) {
            printf("No\n");
            free(H);
            return 0;
        }

        if(current_layer <= H[i]) {
            current_num++;
            if (current_num == m)
            {
                current_num = 0;
                current_layer++;
            }
        }
    }

    printf("Yes\n");
    free(H);
    return 0;
}