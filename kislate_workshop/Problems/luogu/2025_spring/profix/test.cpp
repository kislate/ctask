#include <bits/stdc++.h>
using namespace std;
int n, q;
vector<int> profix;
int main(void)
{
    cin >> n;
    profix.resize(n+1, 0);
    for(int i = 1; i <= n; i++)
    {
        cin >> profix[i];
        profix[i] += profix[i-1];
    }
    cin >> q;
    for(int i = 1; i <= q; i++)
    {
        int l, r;
        cin >> l >> r;
        cout << profix[r] - profix[l-1] << endl;
    }
    return 0;
}