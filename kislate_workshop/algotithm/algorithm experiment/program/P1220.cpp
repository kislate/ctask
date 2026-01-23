#include <bits/stdc++.h>
using namespace std;
int n, c, ans, cost;
vector<int> pos, prefix_sum;
vector<vector<int>> dp1, dp2;
int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); 
    cin >> n >> c;
    // dp1 : left, dp2 : right
    dp1.resize(n + 1, vector<int>(n + 1, 1e9));
    dp2.resize(n + 1, vector<int>(n + 1, 1e9));
    pos.resize(n + 1);

    // from 1 to n, and the first two are dummy
    prefix_sum.insert(prefix_sum.end(), 2, 0);
    for (int i = 1; i <= n; ++i){
        cin >> pos[i] >> cost;
        prefix_sum.push_back(prefix_sum.back() + cost);
    }
    // base case;
    dp1[c][c] = dp2[c][c] = 0;
    for (int i = c; i >= 1; --i){
        for (int j = c; j <= n; ++j){
            dp1[i][j] = min(dp1[i][j], min(
                dp1[i + 1][j] + (prefix_sum[i + 1] + prefix_sum.back() - prefix_sum[j + 1]) * (pos[i + 1] - pos[i]),
                dp2[i + 1][j] + (prefix_sum[i + 1] + prefix_sum.back() - prefix_sum[j + 1]) * (pos[j] - pos[i])
            ));
            
            dp2[i][j] = min(dp2[i][j],  min(
                dp2[i][j - 1] + (prefix_sum[i] + prefix_sum.back() - prefix_sum[j]) * (pos[j] - pos[j - 1]),
                dp1[i][j - 1] + (prefix_sum[i] + prefix_sum.back() - prefix_sum[j] ) * (pos[j] - pos[i])
            ));
        }
    }
    cout << min(dp1[1][n], dp2[1][n]) << endl;
} 


