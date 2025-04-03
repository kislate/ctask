#include <bits/stdc++.h>
using namespace std;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
vector<vector<int>> dp;
queue<pair<int, int>> q;
int n;
bool check(int x, int y)
{
    if(x < 1 || x > n || y < 1 || y > n) return false;
    return true;
}
int main(void)
{
    cin >> n;
    dp.resize(n + 1, vector<int>(n + 1, 0));
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            int temp;
            cin >> temp;
            if(!temp) dp[i][j] = 2;
            else dp[i][j] = temp;
        }
    }
    for(int i = 1; i <= n; i++)
    {
        if(dp[i][1] == 2) dp[i][1] = 0, q.push({i, 1});
        if(dp[i][n] == 2) dp[i][n] = 0, q.push({i, n});
        if(dp[1][i] == 2) dp[1][i] = 0, q.push({1, i});
        if(dp[n][i] == 2) dp[n][i] = 0, q.push({n, i});
    }
    while(!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
        for(int i = 0; i < 4; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if(check(nx, ny) && dp[nx][ny] == 2)
            {
                dp[nx][ny] = 0;
                q.push({nx, ny});
            }
        }
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
