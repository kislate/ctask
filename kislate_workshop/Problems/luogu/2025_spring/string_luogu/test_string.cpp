#include <bits/stdc++.h>
using namespace std;
vector<int> _next;
void get_next(string T, int len)
{
    int j = -1, i = 0;
    _next.resize(len + 1, 0);
    _next[0] = -1;
    // while(i < len)
    // {
    //     while(j != -1 && T[i] != T[j]) j = _next[j];
    //     _next[++i] = ++j;
    // }
    while(i < len)
    {
        while(j != -1 && T[i] != T[j]) j = _next[j];
        i++, j++;
        if(i < len && T[i] == T[j]) _next[i] = _next[j]; // 处理相同字符的情况
        else _next[i] = j; // 处理不同字符的情况
    }
}
int main(void)
{
    string S, T;
    cin >> S >> T;
    int lens = (int)S.length(), lent = (int)T.length();
    get_next(T, lent);
    // KMP algorithm
    int k = 0, m = 0;
    vector<int> pos;
    while(k < lens)
    {
        if(m == lent) // full match
        {
            pos.push_back(k - lent);
            m = _next[m]; // reset m to the next position in T
        }
        if(S[k] == T[m]) k++, m++; // single match success, increment k and m
        else
        {
            if(m == -1 || m== 0) k++;
            else m = _next[m]; // reset m to the next position in T
        }
    }
    for(const int it : pos) cout << it + 1 << endl; // print the positions of matches
    for(int i = 1; i < lent + 1; i++) cout << ((_next[i] == -1) ? 0 : _next[i]) << " "; // print the string T
    return 0;   
}