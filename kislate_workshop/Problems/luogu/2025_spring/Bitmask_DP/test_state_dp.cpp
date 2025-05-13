#include <bits/stdc++.h>
using namespace std;
int main(void)
{
    int n;
    cin >> n;
    while(n--)
    {
        int len;
        cin >> len;
        unordered_set<int> st;
        for(int i = 0; i < len; i++)
        {
            int x;
            cin >> x;
            if(st.find(x) == st.end())
            {
                st.insert(x);
                cout << x << " ";
            }
        }
        cout << endl;          
    }
    return 0;
}