#include <bits/stdc++.h>
using namespace std;
int N, M, S, NM, cur = 0;
vector<int> euler, dep, pos;
vector<bool> visited;
vector<vector<int>> aj, f, rev;
void dfs(int& root) {
    // if (visited[root]) return; // if has visited;
    f[0][cur] = dep[root];
    rev[0][cur] = root;
    pos[root] = cur;
    ++cur;
    for (int u : aj[root]) {
        if (visited[u]) continue; // avoid going back
        visited[u] = true;
        dep[u] = dep[root] + 1;
        dfs(u);
        f[0][cur] = dep[root];
        rev[0][cur] = root;
        ++cur;
    }
    return;
}
int main(void) {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N >> M >> S;
    NM = 2 * N - 1;
    aj.resize(N + 1);
    dep.resize(N + 1);
    pos.resize(N + 1);
    visited.resize(N + 1, false);

    // st init
    vector<int> logn(NM + 1, 0);
    logn[2] = 1;
    for (int i = 3; i <= NM; ++i) logn[i] = logn[i / 2] + 1;
    // index from 0;
    f.resize(logn[NM] + 1, vector<int>(NM));
    // reverse;
    rev.resize(logn[NM] + 1, vector<int>(NM));

    // build euler
    for (int i = 0; i < N - 1; ++i) {
        int x, y;
        cin >> x >> y;
        aj[x].push_back(y);
        aj[y].push_back(x);
    }
    visited[S] = true;
    dep[S] = 0;
    dfs(S);
    
    // st init 
    for (int j = 1; j <= logn[NM]; ++j) {
        for (int i = 0; i + (1 << j) - 1 < NM; ++i) {
            //f[j][i] = max(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);
            if (f[j - 1][i] < f[j - 1][i + (1 << (j - 1))]) {
                f[j][i] = f[j - 1][i];
                rev[j][i] = rev[j - 1][i];
            } else {
                f[j][i] = f[j - 1][i + (1 << (j - 1))];
                rev[j][i] = rev[j - 1][i + (1 << (j - 1))];
            }
        }
    }

    while(M--) {
        int l, r;
        cin >> l >> r;
        l = pos[l], r = pos[r];
        if (l > r) swap(l, r);
        int s = logn[r - l + 1];
        cout << ((f[s][l] < f[s][r - (1 << s) + 1]) ? rev[s][l] : rev[s][r - (1 << s) + 1]) << '\n';
    }
}