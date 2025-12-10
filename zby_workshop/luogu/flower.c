#include <stdio.h>
#include <string.h>

#define MAXF 101
#define MAXV 101
#define NEG_INF -1000000000

int a[MAXF][MAXV];
int dp[MAXF][MAXV];
int pre[MAXF][MAXV];//回溯用，记录上一束花的位置

int main() {
    int F, V;
    scanf("%d %d", &F, &V);

    for (int i = 1; i <= F; i++)
        for (int j = 1; j <= V; j++)
            scanf("%d", &a[i][j]);

    //初始化
    for (int i = 0; i <= F; i++)
        for (int j = 0; j <= V; j++)
            dp[i][j] = NEG_INF;

    //第一束花放在任意 j
    for (int j = 1; j <= V; j++) {
        dp[1][j] = a[1][j];
        pre[1][j] = 0;
    }

    // DP
    for (int i = 2; i <= F; i++) {
        for (int j = i; j <= V; j++) {//至少 j>=i 才能放得下 i 束花
            for (int k = i - 1; k < j; k++) {//上一束花位置必须 < j
                if (dp[i - 1][k] + a[i][j] > dp[i][j]) {
                    dp[i][j] = dp[i - 1][k] + a[i][j];
                    pre[i][j] = k;
                }
            }
        }
    }

    //找最大值
    int best = NEG_INF, pos = -1;
    for (int j = F; j <= V; j++) {
        if (dp[F][j] > best) {
            best = dp[F][j];
            pos = j;
        }
    }

    //回溯
    int ans[MAXF];
    int cur = pos;
    for (int i = F; i >= 1; i--) {
        ans[i] = cur;
        cur = pre[i][cur];
    }

    //输出
    printf("%d\n", best);
    for (int i = 1; i <= F; i++) {
        printf("%d", ans[i]);
        if (i < F) printf(" ");
    }
    printf("\n");

    return 0;
}
