#include <bits/stdc++.h>
using namespace std;
int n, m;
vector<vector<int>> ctl;
vector<int> dp;
int main(void)
{
    cin >> n >> m;
    dp.resize(1 << n, 1e9); // dp[i] 表示mask下需要的次数
    ctl.resize(n + 1, vector<int>(m + 1, 0)); // ctl[i][j]表示i:开关 对j: 的控制方式;
    for(int i = 1; i <= m; i++) for(int j = 1; j <= n; j++) cin >> ctl[i][j]; // i开关控制j灯;
    
}