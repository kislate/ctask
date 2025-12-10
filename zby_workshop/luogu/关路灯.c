#include <stdio.h>
#include <string.h>

#define INF 9999999999999

int n, c;
long long pos[55], w[55], sumW[55];//位置，功率，功率和
long long dp[55][55][2];//记录状态

int main() {
    scanf("%d %d", &n, &c);
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld", &pos[i], &w[i]);
        sumW[i] = sumW[i - 1] + w[i];
    }

    //初始化 DP
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dp[i][j][0] = dp[i][j][1] = INF;

    dp[c][c][0] = dp[c][c][1] = 0;

    //按区间长度进行枚举
    for (int len = 1; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;

            long long remain = sumW[n] - (sumW[r] - sumW[l - 1]);

            if (dp[l][r][0] < INF) {
                //从l扩展到l-1
                if (l > 1) {
                    long long cost = remain * (pos[l] - pos[l - 1]);
                    if (dp[l - 1][r][0] > dp[l][r][0] + cost)
                        dp[l - 1][r][0] = dp[l][r][0] + cost;
                }
                //从l扩展到r+1
                if (r < n) {
                    long long cost = remain * (pos[r + 1] - pos[l]);
                    if (dp[l][r + 1][1] > dp[l][r][0] + cost)
                        dp[l][r + 1][1] = dp[l][r][0] + cost;
                }
            }

            if (dp[l][r][1] < INF) {
                //从 r 扩展到 l-1
                if (l > 1) {
                    long long cost = remain * (pos[r] - pos[l - 1]);
                    if (dp[l - 1][r][0] > dp[l][r][1] + cost)
                        dp[l - 1][r][0] = dp[l][r][1] + cost;
                }
                //从 r 扩展到 r+1
                if (r < n) {
                    long long cost = remain * (pos[r + 1] - pos[r]);
                    if (dp[l][r + 1][1] > dp[l][r][1] + cost)
                        dp[l][r + 1][1] = dp[l][r][1] + cost;
                }
            }
        }
    }

    long long ans = dp[1][n][0];
    if (dp[1][n][1] < ans)
        ans = dp[1][n][1];

    printf("%lld\n", ans);
    return 0;
}
