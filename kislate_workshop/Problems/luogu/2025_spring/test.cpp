#include <bits/stdc++.h>
using namespace std;
int main(void)
{
    int MAX_VOLUME;
    int SUM_GOODS;
    cin >> MAX_VOLUME >> SUM_GOODS;
    vector<int> goods(SUM_GOODS);
    vector<int> dp(MAX_VOLUME + 1, 0);
    for(int i = 0; i < SUM_GOODS; i++){
        cin >> goods[i];
        for(int j = MAX_VOLUME; j >= goods[i]; j--)
            dp[j] = max(dp[j], dp[j - goods[i]] + goods[i]);
    }
    cout << MAX_VOLUME-dp[MAX_VOLUME] << endl;
}