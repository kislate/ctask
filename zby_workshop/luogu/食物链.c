#include <stdio.h>
#include <string.h>

#define MAXN 5005
#define MAXM 500000

int head[MAXN], to[MAXM], nxt[MAXM], edge_cnt = 0;
int indeg[MAXN], outdeg[MAXN];
int queue[MAXN];// 用于拓扑排序
int dp_len[MAXN], dp_cnt[MAXN];//最长路径长度与个数

void add_edge(int u, int v) {
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt++;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    memset(head, -1, sizeof(head));//初始化邻接表

    for (int i = 0; i < m; i++) {
        int A, B;
        scanf("%d %d", &A, &B);
        add_edge(A, B);
        indeg[B]++;//统计入度
        outdeg[A]++;//统计出度
    }

    //拓扑排序
    int qh = 0, qt = 0;
    for (int i = 1; i <= n; i++)
        if (indeg[i] == 0) queue[qt++] = i;

    //DP初始化
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) {
            dp_len[i] = 1;
            dp_cnt[i] = 1;
        }
    }

    //按拓扑序DP
    while (qh < qt) {
        int u = queue[qh++];

        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];

            //标准最长路DP
            if (dp_len[u] + 1 > dp_len[v]) {
                dp_len[v] = dp_len[u] + 1;
                dp_cnt[v] = dp_cnt[u];
            }//更新路径数
            else if (dp_len[u] + 1 == dp_len[v]) {
                dp_cnt[v] = (dp_cnt[v] + dp_cnt[u]) % 80112002;
            }

            indeg[v]--;
            if (indeg[v] == 0) queue[qt++] = v;
        }
    }

    //找出度为0的最长链
    int max_len = 0;
    for (int i = 1; i <= n; i++)
        if (outdeg[i] == 0 && dp_len[i] > max_len)
            max_len = dp_len[i];

    //统计条数
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        if (outdeg[i] == 0 && dp_len[i] == max_len)
            ans = (ans + dp_cnt[i]) % 80112002;

    printf("%lld\n", ans);
    return 0;
}
