#include <bits/stdc++.h>
using namespace std;
vector<char> a, b;
stack<char> s;
void delet(char ch)
{
    int idx1 = find(a.begin(), a.end(), ch) - a.begin();
    int idx2 = find(b.begin(), b.end(), ch) - b.begin();
    if(idx1 == a.size() || idx2 == b.size()) return;
    a.erase(a.begin() + idx1);
    b.erase(b.begin() + idx2);
}
void dfs(char root);
int main(void)
{
    string s1, s2;
    cin >> s1 >> s2;
    int len = s2.length();
    for(const auto &c : s1) a.push_back(c);
    for(const auto  &c : s2) b.push_back(c);
    dfs(s2[len - 1]);
    // 先序遍历
    while(!s.empty()){
        char ch = s.top();
        cout << ch;
        s.pop();
    }
    cout << endl;
    return 0;
}

void dfs(char root)
{
    if(a.empty() || b.empty()) return;
    delet(root); 
    int idx1 = find(a.begin(), a.end(), root) - a.begin();
    int idx2 = find(b.begin(), b.end(), root) - b.begin();
    char rroot = b[idx2 - 1];
    char lroot = b[idx1 - 1];
    if(idx1 > 0) dfs(rroot);
    s.push(root);
    if(idx2 > 0 && lroot != rroot) dfs(lroot);

}

// BADC 中序
// BDCA 后序
// ABCD 前序
// 示意图:
/*
        A
       / \
      B   C
         / 
        D   
*/