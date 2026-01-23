// 标准的ST表解法展现忠诚
#include <bits/stdc++.h>
using namespace std;
int main(void) {
    ios::sync_with_stdio(false); cin.tie(0);
    int m, n;
    cin >> m >> n;
    vector<int> logn(m + 1, 0);
    logn[2] = 1;
    for (int i = 3; i <= m; ++i) logn[i] = logn[i / 2] + 1;
    vector<vector<int>> f(logn[m] + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= m; ++i) cin >> f[0][i];
    for (int j = 1; j <= logn[m]; ++j) {
        for (int i = 1; i + (1 << j) - 1 <= m; ++i) {
            f[j][i] = min(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);
        } 
    }
    while(n--) {
        int l, r, s;
        cin >> l >> r;
        s = logn[r - l + 1];
        cout << min(f[s][l], f[s][r - (1 << s) + 1]) << " ";
    }
    return 0;
}
