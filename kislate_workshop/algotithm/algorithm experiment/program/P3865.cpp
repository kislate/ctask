#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> logn(n + 1, 0); // n + 1
    // logn[1] = 0, 所以不能全都初始化为1
    logn[2] = 1;
    // 预计算log值
    for (int i = 3; i <= n; ++i) logn[i] = logn[i / 2] + 1;
    vector<vector<int>> f(logn[n] + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i) cin >> f[0][i];
    for (int j = 1; j <= logn[n]; ++j) {
        for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
            f[j][i] = max(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);
        }
    }
    while (m--) {
        int l, r;
        cin >> l >> r;
        int tmp = logn[r - l + 1];
        cout << max(f[tmp][l], f[tmp][r - (1 << tmp) + 1]) << '\n';
    } 
    return 0;
}