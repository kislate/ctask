#include <bits/stdc++.h>
using namespace std;
unordered_set<string> myset;
vector<bool> dp;
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string temp;
    while(cin >> temp)
    {
        if(temp == ".") break;
        myset.insert(temp);
    }
    cin.ignore();  // 清理缓冲区中的换行符
    string s, line;
    for(string temp;cin>>temp;s+=temp);
    int len = (int)s.length();
    dp.resize(len + 1, false);
    dp[0] = true;
    int ans = 0;
    for(int i = 1; i <= len; i++)  // 从1开始
    {
        for(int j = 0; j < i; j++)
        {
            if(dp[j] && myset.count(s.substr(j, i - j)))
            {
                dp[i] = true;
                ans = max(ans, i);
                break;
            }
        }
    }
    cout << ans << endl;
    return 0;
}