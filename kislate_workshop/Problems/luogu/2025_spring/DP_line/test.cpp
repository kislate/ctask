#include <bits/stdc++.h>
using namespace std;
vector<int> mem;
vector<vector<vector<int>>> ans;
vector<vector<int>> dfs(int i);
int main()
{
    int n;
    cin >> n;
    ans.resize(n + 1);
    mem.resize(n+1);
    ans[n] = dfs(n);
    for(auto& vec : ans[n]) sort(vec.begin(), vec.end());
    sort(ans.begin(), ans.end());
    for(const auto& vec : ans[n])
    {
        cout << vec[0];
        for(int i = 1; i < vec.size(); i++)
        {
            cout << "+" << vec[i];
        }
        cout << endl;
    }
}
vector<vector<int>> dfs(int i)
{
    if(i == 1) return {{1}};
    if(mem[i]) return ans[i];
    vector<vector<int>> res;
    for(int j = i-1; j >= 1; j--)
    {
        vector<vector<int>> temp = dfs(i - j);
        for(auto& vec : temp)
        {
            vec.push_back(j);
            res.push_back(vec);
        }
    }
    return ans[i] =res;
}