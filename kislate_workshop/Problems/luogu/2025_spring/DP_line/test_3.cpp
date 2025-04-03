// 这里是没有dfs的计算
#include <bits/stdc++.h>
using namespace std;
int main(void) 
{
    // input
    string line;
    getline(cin, line);
    istringstream iss(line);
    int height;
    vector<int> heights;
    while(iss >> height) heights.push_back(height);
    // 

    int n = heights.size();// 长度
    vector<int> dp(n, 1);
    vector<int> dp2(n, 1);
    int ans = 0;
    int cnt = 0;
    for(int i = n-1; i >= 0; i--)// 从后往前遍历
    {
        for(int j = i + 1; j < n; j++)// 向后找最优解
        {
            if(heights[j] <= heights[i]) dp[i] = max(dp[i], dp[j] + 1);
            else if(heights[j] > heights[i]) dp2[i] = max(dp2[i], dp2[j] + 1);
        }
        //dp[i] = max(dp[i], dp[j] + 1);
        ans = max(ans, dp[i]);
        cnt = max(cnt, dp2[i]);
    }
    
    cout << ans << endl;
    cout << cnt << endl;
    //for(int i = 0; i < n; i++) cout << dp[i] << " ";
    //cout << endl;
    return 0;
}