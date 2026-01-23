#include <bits/stdc++.h>
using namespace std;
int N, K, ans = 0;
vector<int> fa, dist;
int find(int i) { 
    if (fa[i] == i) return i;
    int root = find(fa[i]);
    dist[i] = (dist[i] + dist[fa[i]]) % 3;
    return fa[i] = root;
}
int main(void) {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N >> K;
    fa.resize(N + 1);
    dist.resize(N + 1, 0);
    iota(fa.begin(), fa.end(), 0);
    while(K--) {
        int op, X, Y;
        cin >> op >> X >> Y;
        if (X > N || Y > N || (op == 2 && X == Y)) {
            ++ans;
            continue;
        }
        int rootX = find(X), rootY = find(Y);
        if (op == 1) {
            if (rootX == rootY) {
                if (dist[X] % 3 != dist[Y] % 3) {
                    ++ans;
                    continue;
                }
            } else {
                fa[rootX] = rootY;
                // 6，C++ 模要是正数
                dist[rootX] = (dist[Y] - dist[X] + 3) % 3;
            }
        } else {
            if (rootX == rootY) {
                if ((dist[Y] - dist[X] + 3) % 3 != 1) {
                    ++ans;
                    continue;
                }
            } else {
                fa[rootX] = rootY;
                dist[rootX] = (dist[Y] - dist[X] - 1 + 3) % 3;
            }
        }
    }
    cout << ans << endl;
}