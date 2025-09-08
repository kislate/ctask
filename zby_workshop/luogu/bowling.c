#include<stdio.h>
#include<stdlib.h>
int main() {
    int n,q;
    scanf("%d", &n);
    int *a = (int *)malloc((n+1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int k;
        scanf("%d", &k);
        int flag = 0;
        for(int j = 1; j <= n; j++) {
            if (a[j] == k) {
                printf("%d\n", j);
                flag = 1;
                break;
            }
        }
        if (flag==0) {
            printf("0\n");
        }
    }
    return 0;
}