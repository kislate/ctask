// update 时更新距离即可
#include <bits/stdc++.h>
using namespace std;
vector<int> fa, sz, dist;
int find(int i) {
    if (fa[i] == i) return i;
    int root = find(fa[i]);
    dist[i] += dist[fa[i]];
    return fa[i] = root;
}
int main(void) {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    int N = 30000;
    fa.resize(N + 1);
    sz.resize(N + 1, 1);
    dist.resize(N + 1, 0);
    iota(fa.begin(), fa.end(), 0);

    while(T--) {
        char op; 
        cin >> op;
        int i, j;
        cin >> i >> j;
        int rootx = find(i), rooty = find(j);
        if (op == 'M') {
            if (rootx != rooty) {
                fa[rootx] = rooty;
                dist[rootx] = sz[rooty];
                sz[rooty] += sz[rootx];
            }
        } else {
            if (rootx != rooty) {
                cout << -1 << endl;
            } else {
                cout << abs(dist[i] - dist[j]) - 1 << endl;
            }
        }
    }
    return 0;
}   