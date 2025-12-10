#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 1005
#define MAXE (MAXN * 2)

int head[MAXN], to[MAXE], nxt[MAXE], etot;
int N;

//添加无向边 u - v
void add_edge(int u, int v) {
    to[etot] = v; nxt[etot] = head[u]; head[u] = etot++;
    to[etot] = u; nxt[etot] = head[v]; head[v] = etot++;
}

int cmp(const void* a, const void* b) {
    return *(int*)b - *(int*)a;
}

int dfs_dp(int u, int parent) {

    int times[MAXN];
    int cnt = 0;

    //收集所有孩子子树传播所需时间
    for (int e = head[u]; e != -1; e = nxt[e]) {
        int v = to[e];
        if (v == parent) continue;//不往父节点方向走
        times[cnt++] = dfs_dp(v, u);
    }

    //若没有孩子，则此节点传播时间为 0
    if (cnt == 0) return 0;

    qsort(times, cnt, sizeof(int), cmp);

    int best = 0;
    for (int i = 0; i < cnt; i++) {
        int finish = times[i] + (i + 1);
        if (finish > best) best = finish;
    }

    return best;
}

int main() {
    scanf("%d", &N);

    memset(head, -1, sizeof(head));
    etot = 0;

    int p;
    for (int i = 2; i <= N; i++) {
        scanf("%d", &p);
        add_edge(i, p);
    }

    int dp[MAXN];
    int best = 1e9;

    for (int i = 1; i <= N; i++) {
        dp[i] = dfs_dp(i, 0);  //假设i已经在时间0知道消息
        if (dp[i] < best) best = dp[i];
    }

    printf("%d\n", best + 1);

    //输出所有达到最小时间的节点
    int first = 1;
    for (int i = 1; i <= N; i++) {
        if (dp[i] == best) {
            if (!first) printf(" ");
            printf("%d", i);
            first = 0;
        }
    }
    printf("\n");
    return 0;
}
