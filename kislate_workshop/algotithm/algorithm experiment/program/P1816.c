#include <stdio.h> 
// 这道题的测试很水，直接c语言暴力过
int main(void) {
    int m, n;
    scanf("%d%d", &m, &n);
    int bills[m + 1];
    for (int i = 1; i <= m; ++i) scanf("%d", bills + i);
    for (int i = 0; i < n; ++i) {
        int ans = 1e9;
        int l, r;
        scanf("%d%d", &l, &r);
        for (int j = l; j <= r; ++j) {
            if (ans > bills[j]) ans = bills[j];
        }
        printf("%d ", ans);
    }
}