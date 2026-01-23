#include <bits/stdc++.h>
using namespace std;
int F, V, ans = -1e9;
// i after pos j;
vector<vector<int>> values, memo, prepos;
void search(int i, int pos){
    if (i > F || V - pos < F - i) return;
    if (memo[i][pos] != -1e9) return;
    for (int j = V - (F - i) + 1; j >=  pos + 1; --j) {
        search(i + 1, j);
        // memo[i][pos] = max(memo[i][pos], memo[i + 1][j] + values[i][pos]);
        if (memo[i][pos] < memo[i + 1][j] + values[i][pos]) {
            memo[i][pos] = memo[i + 1][j] + values[i][pos];
            prepos[i][pos] = j;
        }
    }
    return;
}
int main(void) {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> F >> V;
    values.resize(F + 1, vector<int>(V + 1));
    memo.resize(F + 1, vector<int>(V + 1, -1e9));
    prepos.resize(F + 1, vector<int>(V + 1, -1));
    for (int i = 1; i <= F; ++i) {
        for (int j = 1; j <= V; ++j) cin >> values[i][j];
    }
    memo[F][V] = values[F][V];
    for (int i = V - 1; i >= F; --i) memo[F][i] = max(memo[F][i + 1], values[F][i]);
    for (int i = V - F + 1; i >= 1; i--) search(1, i);
    int start_pos = -1;
    for (int i = 1; i <= V - F + 1; ++i) {
        if (memo[1][i] > ans) {
            ans = memo[1][i];
            start_pos = i;
        }
    }
    cout << ans << endl;
    for (int i = 1; i <= F; ++i) {
        cout << start_pos;
        start_pos = prepos[i][start_pos];
        if (i != F) cout << " ";
    }
    return 0;
}
