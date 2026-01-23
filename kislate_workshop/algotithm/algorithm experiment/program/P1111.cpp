#include <bits/stdc++.h>
using namespace std;
struct edge {
    int x, y, t;
};
// blocks
int cnt;
vector<int> fa;
vector<edge> edges;
int find(int& i) {
    return fa[i] == i ? i : fa[i] = find(fa[i]);
}
int main(void) {
    int N, M;
    cin >> N >> M;
    cnt = N;
    fa.resize(N + 1);
    edges.resize(M);
    iota(fa.begin(), fa.end(), 0);
    for (int i = 0; i < M; ++i) {
        cin >> edges[i].x >> edges[i].y >> edges[i].t;
    }
    sort(edges.begin(), edges.end(), [](const edge&a, edge& b){
        return a.t < b.t;
    });
    for (auto& e : edges) {
        int rootx = find(e.x);
        int rooty = find(e.y);

        if (rootx != rooty) {
            fa[rootx] = rooty; // 合并
            cnt--;
        }

        if (cnt == 1) {
            cout << e.t << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}