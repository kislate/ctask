#include <bits/stdc++.h>
using namespace std;
int main(void)
{
    int n, sum;
    cin >> n;
    sum = pow(2, n);
    vector<pair<int, int>> a(sum+1, {0, 0});
    for(int i = 1; i <= sum; i++)
    {
        cin >> a[i].first;
        a[i].second = i;
    }
    while(n>1)
    {
        for(int i = 1; i <= sum; i++)
        {
            if(a[i*2-1].first > a[i*2].first)
            {
                a[i].first = a[i*2-1].first;
                a[i].second = a[i*2-1].second;
            }
            else
            {
                a[i].first = a[i*2].first;
                a[i].second = a[i*2].second;
            }
        }
        sum /= 2;
        n--;
    }
    if(a[1].first > a[2].first)
    {
        cout << a[2].second << endl;
    }
    else
    {
        cout << a[1].second << endl;
    }
    return 0;
}