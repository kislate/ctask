#include<stdio.h>
#include<stdlib.h>
int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int* a = (int*)malloc((n+1) * sizeof(int));
    int b[30001]={0};
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[a[i]] = 1;
    }
    int count = 0;
    for (int i = 1; i < 30001; i++) {
        if (b[i] == 1) {
            count++;
        }
        if (count == k) {
            printf("%d", i);
            free(a);
            return 0;
        }
    }
    printf("NO RESULT");
    free(a);
    return 0;
}