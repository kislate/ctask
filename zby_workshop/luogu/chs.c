#include<stdio.h>
#include<stdlib.h>

void quicksort(int *a, int left, int right) {
    if (left >= right) return;
    int i = left, j = right, pivot = a[left];
    while (i < j) {
        while (i < j && a[j] >= pivot) j--;
        if (i < j) a[i++] = a[j];
        while (i < j && a[i] <= pivot) i++;
        if (i < j) a[j--] = a[i];
    }
    a[i] = pivot;
    quicksort(a, left, i - 1);
    quicksort(a, i + 1, right);
}

int main() {
    int n,p;
    scanf("%d %d", &n, &p);
    int *a=(int *)malloc((n+1) * sizeof(int));
    int *d=(int *)malloc((n+1) * sizeof(int));
    a[0] = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for(int i=0;i<=p;i++)
    {
        int x,y,z;
        scanf("%d %d %d", &x, &y, &z);
        d[x] += z;
        d[y + 1] -= z;
    }
    int add = 0;
    for (int i = 1; i <= n; i++) {
        add += d[i];
        a[i] += add;
    }
    quicksort(a, 1, n);
    printf("%d ", a[1]);
    free(a);
    free(d);
    return 0;
}