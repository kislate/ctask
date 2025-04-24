#include <bits/stdc++.h>
using namespace std;
int n, mem[25], max_len = 0;
char head;
string s[25], final_ans = "";
bool match(int idx, int j, int i);
void dfs(int idx, int len, string ans);
int main(void)
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> s[i];
    cin >> head;
    for(int i = 1; i <= n; i++)
    {
        if(s[i][0] == head)
        {
            // 以head为开头的单词
            string ans = s[i];
            mem[i] = 1;
            dfs(i, s[i].length(), ans);
            mem[i] = 0;
        }
    }
    cout << max_len << endl;
    // cout << final_ans << endl;
}
// 从 idx 的 j位开始, 看能否接上 i 的 j 位
bool match(int idx, int j, int i)
{
    string nstr = s[idx];
    string str = s[i];
    string nstrcut = nstr.substr(j, nstr.length() - j);
    string strcut = str.substr(0, nstr.length() - j);
    // 保证没有包含关系, 确认首尾相连:
    if(nstrcut == strcut && nstrcut.length() > 0 && strcut.length() != str.length() && nstrcut.length() != nstr.length())
    {
        //cout << "match: " << nstr << " " << str << " " << "from " << nstrcut << " " << strcut << endl;
        return true;
    }
    //cout << "not match: " << nstr << " " << str << " " << "from " << nstrcut << " " << strcut << endl;
    return false;
}
void dfs(int idx, int len, string ans)
{
    if(len > max_len) max_len = len, final_ans = ans; // 更新最大长度和对应的字符串
    for(int j = 0; j < s[idx].length(); j++)
    {
        for(int i = 1; i <= n; i++)
        {
            // if(i == idx) continue; // 不能和自己连接
            if(match(idx, j, i))
            {
                if(mem[i] > 1) continue; // 超过两次
                mem[i]++;
                string nans = ans + s[i].substr(s[idx].length() - j, s[i].length());
                // cout << "nans " << nans << endl;
                dfs(i, len + s[i].length() - (s[idx].length() - j), nans);
                mem[i]--;
            }
        }
    }
}

