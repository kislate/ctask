#include <bits/stdc++.h>
using namespace std;
int max_five(int a, int b, int c, int d, int e)
{
    return max(a, max(b, max(c, max(d, e))));
}
int main(void)
{
    int row, col, max_length = 1;
    cin >> row >> col;
    vector<vector<int>> map_height(row+2, vector<int>(col+2, 0)), dp(row+2, vector<int>(col+2, 1));
    for(int i = 1; i < row; i++) for(int j = 0; j < col; j++) cin >> dp[i][j];
    for(int i = 1; i <= row; i++)
    {
        for(int j = 1; j <= col; j++)
        {
            if(map_height[i+1][j] > map_height[i][j])    dp[i+1][j] = max(dp[i][j] + 1, dp[i+1][j]);
            if(map_height[i-1][j] > map_height[i][j])    dp[i-1][j] = max(dp[i][j] + 1, dp[i-1][j]);
            if(map_height[i][j+1] > map_height[i][j])    dp[i][j+1] = max(dp[i][j] + 1, dp[i][j+1]);
            if(map_height[i][j-1] > map_height[i][j])    dp[i-1][j-1] = max(dp[i][j] + 1, dp[i][j-1]);
            max_length = max_five(max_length, dp[i+1][j], dp[i-1][j], dp[i][j+1], dp[i][j-1]);
        }
    }
    cout << max_length << endl;
    return 0;
}