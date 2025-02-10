#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int total_dx = 0, total_dy = 0;
    for (int i = 0; i < n; i++) {
        int dxi, dyi;
        scanf("%d %d", &dxi, &dyi);
        total_dx += dxi;
        total_dy += dyi;
    }
    int* x = (int*)malloc(sizeof(int) * m);
    int* y = (int*)malloc(sizeof(int) * m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    for(int i=0;i<m;i++){
        int new_x = x[i] + total_dx;
        int new_y = y[i] + total_dy;
        printf("%d %d\n", new_x, new_y);
    }
    free(x);
    free(y);
    return 0;
}