#include <bits/stdc++.h>
using namespace std;
// 不用long long会爆int
int main(void)
{
    long long n, x;
    cin >> n >> x;
    vector<long long> loses(n);
    vector<long long> wins(n);
    vector<long long> uses(n);
    vector<long long> dp(x+1);
    for(long long i = 0; i < n; i++) cin >> loses[i] >> wins[i] >> uses[i];
    for(long long i = 0; i < n; i++)
    {
        for(long long j = x; j >= 0; j--)
        {
            if(j < uses[i])
                dp[j] += loses[i];
            else
                dp[j] = max(dp[j] + loses[i] ,dp[j-uses[i]] + wins[i]);
        }
    }
    cout << dp[x]*5 << endl;
    return 0;
}