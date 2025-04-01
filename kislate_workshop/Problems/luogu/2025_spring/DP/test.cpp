#include <bits/stdc++.h>
using namespace std;
void print(int i, vector<int> prior){
    if(prior[i] == 0) 
    {
        printf("%d", i);
        return;
    }
    else
    {
        print(prior[i], prior);
        printf(" %d", i);
    }
}
int main(void){
    int N;
    cin >> N;
    vector<int> prior(N + 1, 0), dp(N + 1, 0), num(N + 1, 0);
    vector<vector<int>> path(N + 1, vector<int>(N + 1, 0));
    for(int i = 1; i <= N; i++) cin >> num[i];
    for(int i = 1; i <= N-1; i++) for(int j = i + 1; j <= N; j++) cin >> path[i][j];
    int ans = num[1], ans_index = 1;
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++)
        {
            if(path[j][i] && dp[i] < dp[j]) dp[i] = dp[j], prior[i] = j;
        }
        dp[i] += num[i];
        if(dp[i] > ans) ans = dp[i], ans_index = i;
    }
    print(ans_index, prior);
    cout << endl;
    cout << ans << endl;
}