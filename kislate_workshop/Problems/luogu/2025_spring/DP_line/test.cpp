/*
    P2679 子串 DP
    2025.4.18
*/
#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007
int main(void)
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<char> s1(n), s2(m);
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for(int i = 0; i < n; i++) cin >> s1[i];
    for(int i = 0; i < m; i++) cin >> s2[i];
} 