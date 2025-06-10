#include <bits/stdc++.h>
using namespace std;
int n, m;
unordered_map<string, int> mp;
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        mp[s] = 1;
    }
    cin >> m;
    for(int i = 0; i < m; i++)
    {
        string s;
        cin >> s;
        if(mp.find(s) == mp.end()) cout << "WRONG" << endl;
        else if(mp[s] == 1)
        {
            cout << "OK" << endl;
            mp[s] = 2;
        }
        else if(mp[s] == 2) cout << "REPEAT" << endl;
    }
    return 0;
}