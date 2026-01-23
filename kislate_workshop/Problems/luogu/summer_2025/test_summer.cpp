#include <bits/stdc++.h>
using namespace std;
unordered_set<string> myset;
vector<bool> dp;
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string temp;
    int maxlen = 0;
    while(cin >> temp)
    {
        if(temp == ".") break;
        maxlen = max(maxlen, (int)temp.length());
        myset.insert(temp);
    }
    cin.ignore();  // 清理缓冲区中的换行符
    string s, line;
    for(string temp;cin>>temp;s+=temp);
    int len = (int)s.length();
    dp.resize(len + 1, false);
    dp[0] = true;
    int ans = 0, missing = 0;
    for(int i = 1; i <= len; i++)  // 从1开始
    {
        bool flag = false;
        for(int j = max(i - maxlen, 0); j < i; j++)
        {
            if(dp[j] && myset.count(s.substr(j, i - j)))
            {
                dp[i] = true;
                ans = max(ans, i);
                flag = true;
                break;
            }
        }
    }
    cout << ans << endl;
    return 0;
}