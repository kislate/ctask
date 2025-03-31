#include <bits/stdc++.h>
using namespace std;
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};
int heights[102][102], sum[102][102], R, C;
int search(int x, int y);
int main(void){
    int ans = -1e4;
    cin >> R >> C;
    for(int i = 1; i <= R; i++) for(int j = 1; j <= C; j++) cin >> heights[i][j];
    for(int i = 1; i <= R; i++) for(int j = 1; j<= C; j++) ans = max(ans, search(i, j));
    cout << ans << endl;
}
int search(int x, int y)
{
    if(sum[x][y]) return sum[x][y];
    sum[x][y] = 1;
    int nx, ny;
    for(int i = 0; i < 4; i++)
    {
        nx = x + dx[i], ny = y + dy[i];
        if(nx >= 0 && nx <= R && ny >= 0 && ny <= C && heights[x][y] > heights[nx][ny]) sum[x][y] = max(sum[x][y], search(nx, ny) + 1);
    }
    return sum[x][y];
}