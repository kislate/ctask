#include <stdio.h>
#include <string.h>

#define MAXN 6005

int n;
int r[MAXN];
int head[MAXN], nxt[MAXN], to[MAXN], tot = 0;
int has_parent[MAXN];//用来找根

int dp[MAXN][2];//dp[u][0/1]

//加边
void add(int u, int v) {
    to[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}

void dfs(int u) {
    dp[u][1] = r[u];
    dp[u][0] = 0;

    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        dfs(v);
        dp[u][1] += dp[v][0];//u来，则v不能来
        dp[u][0] += (dp[v][0] > dp[v][1] ? dp[v][0] : dp[v][1]); //u不来，则v可来可不来
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &r[i]);

    for (int i = 1; i <= n - 1; i++) {
        int l, k;
        scanf("%d %d", &l, &k);
        add(k, l);        //k是上司，所以k -> l
        has_parent[l] = 1;//l有父亲
    }

    int root = 1;
    for (int i = 1; i <= n; i++)
        if (!has_parent[i])
            root = i;

    dfs(root);

    int ans = dp[root][0] > dp[root][1] ? dp[root][0] : dp[root][1];
    printf("%d\n", ans);
    return 0;
}
