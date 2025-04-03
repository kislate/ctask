#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long
vector<vector<int>> ans;
vector<int> temp;
vector<string> ans_str;
void dfs(int i);
int main(void){
    int n;
    cin >> n;
    dfs(n);
    for(auto& vec: ans) sort(vec.begin(), vec.end(), [](int a, int b){ return a < b; });
    sort(ans.begin(), ans.end(), [](const vector<int>& a, const vector<int>& b){
        for(ull i = 0; i < min(a.size(), b.size()); i++){
            if(a[i] != b[i]) return a[i] < b[i];
        }
        return a.size() < b.size();
    });


    for(ull i = 0; i < ans.size(); i++){
        string str = "";
        str+= to_string(ans[i][0]);
        for(ull j = 1; j < ans[i].size(); j++){
            str = str + "+" + to_string(ans[i][j]);
        }
        if(find(ans_str.begin(), ans_str.end(), str) == ans_str.end()) ans_str.push_back(str);
    }
    for(ull i = 0; i < ans_str.size()-1; i++){
        cout << ans_str[i] << endl;
    }
    return 0;
}
void dfs(int i)
{
    if(i == 0){
        ans.push_back(temp);
        return;
    }
    if(i == 1){
        temp.push_back(1);
        ans.push_back(temp);
        temp.pop_back();
        return;
    }
    for(int j = i; j >= 1; j--)
    {
        temp.push_back(j);
        dfs(i - j);
        temp.pop_back();
    }
}