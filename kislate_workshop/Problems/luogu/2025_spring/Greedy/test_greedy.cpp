#include <bits/stdc++.h>
using namespace std;
int main(void)
{
    int n, ans = 1e9;
    cin >> n;
    map<int, int> power_map;
    vector<pair<int, int>> power_sum;
    for(int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        power_map[x]++;
    }
    for(auto it : power_map) power_sum.push_back(it);
    int len = (int)power_sum.size();
    for(int i = 0; i < len; i++)
    {
        while(power_sum[i].second > 0)
        {
            int cnt = 0;
            for(int j = i; j < len; j++)
            {
                if(((j == len-1) || power_sum[j+1].first - power_sum[j].first != 1) || (power_sum[j+1].second < power_sum[j].second))
                {
                    power_sum[j].second--;
                    cnt++;
                    ans = min(ans, cnt);
                    break;
                }
                else{
                    power_sum[j].second--;
                    cnt++;
                }
            }
            ans = min(ans, cnt);
        }
    }
    cout << ans << endl;
    return 0;
}
