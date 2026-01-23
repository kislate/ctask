#include <bits/stdc++.h>
using namespace std;
int N;
vector<char> S;
vector<vector<int>> dp;
void cover(int l, int r) {
    if (dp[l][r] != 1e9) return;
    if (l == r) {
        dp[l][r] = 1;
        return;
    }
    for (int k = l; k < r; k++) {
        cover(l, k);
        cover(k + 1, r);
        dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r]);
    }
    if (S[l] == S[r]) {
        dp[l][r] -= 1;
    }
}
int main(void) {
    ios::sync_with_stdio(false); cin.tie(0);
    char c;
    while(cin >> c) S.push_back(c);
    N = S.size();
    dp.resize(N, vector<int>(N, 1e9));
    for(int i = 0; i < N; i++) dp[i][i] = 1;
    cover(0, N - 1);
    cout << dp[0][N - 1] << endl;
    return 0;
}