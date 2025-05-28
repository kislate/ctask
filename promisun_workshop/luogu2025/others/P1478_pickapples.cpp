#include <bits/stdc++.h>
using namespace std;
int n,s,a,b;
vector<pair<int, int>> apples;
int main(void)
{
    cin >> n >> s >> a >> b;
    int ok=a+b;
    
    apples.resize(n, {0, 0});
    for(int i=0;i<n;i++)
    {
        cin >> apples[i].first >> apples[i].second;
    }
    sort(apples.begin(), apples.end(), [](pair<int, int> x, pair<int, int> y) {
        return x.second < y.second;
    });
    // for(int i = 0; i < n; i++) cout << apples[i].first << " " << apples[i].second << endl;
    int ans = 0;
    for(int i=0;i<n && s>0 ;i++)
    {
        if(apples[i].first <=ok &&  s-apples[i].second >= 0)
        {
            ans++;
            s-=apples[i].second;
        }
    }
    cout << ans << endl;
}
