
#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
ull W, n;
vector<pair<ull, ull>> peoples;
bool isValid(ull state)
{
    ull sum = 0;
    for(ull i = 0; i < n; i++)
    {
        sum += peoples[i].second * ((state >> i) & 1);
        if(sum > W) return false;
    }
    return true;
}
ull getTime(ull state)
{
    ull time = 0;
    for(ull i = 0; i < n; i++)
    {
        if(state & (1 << i))
        {
            time = max(time, peoples[i].first);
        }
    }
    return time;
}
int main(void)
{
    cin >> W >> n;
    peoples.resize(n);
    for(ull i = 0; i < n; i++) cin >> peoples[i].first >> peoples[i].second;
    vector<ull> dp(1 << n, 1e9);
    dp[0] = 0;
    for(ull i = 0; i < (1 << n); i++)
    {
        ull rest = ((1 << n) - 1) ^ i;
        for(ull j = rest; j; j = (j - 1) & rest)
        {
            if(!isValid(j)) continue;
            ull next = i | j;
            dp[next] = min(dp[next], dp[i] + getTime(j));
        }
    }
    cout << dp[(1 << n) - 1] << endl;
    return 0;
}
