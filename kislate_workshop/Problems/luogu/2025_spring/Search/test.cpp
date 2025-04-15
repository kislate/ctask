#include <bits/stdc++.h>
using namespace std;
int dx[4] = {-1, 0, 1, 0 };
int dy[4] = {0, -1, 0, 1 };
int n, m, ans = 0;
vector<vector<vector<vector<int>>> dp;
vector<vector<int>> maze;
struct cmp{
    bool operator()(const tuple<int, int, int, int, int>& a, const tuple<int, int, int, int, int>& b)
    {
        return get<0>(a) > get<0>(b);
    }
};
int check(int nx, int ny, int color, int &magic, int magic)
{
    if(nx < 1 || nx > n || ny < 1 || ny > m) return 0;
    if(maze[nx][ny] == color && !dp[nx][ny][color][magic]) return 1;
    if(maze[nx][ny] != 0 && !dp[nx][ny][maze[nx][ny]][magic]) return 2;
    if(maze[nx][ny] == 0 && !magic) return 0;
    if(maze[nx][ny] == 0 && magic) return 3;
    return 0;
}
int main(void)
{
    cin >> n >> m;
    dp.resize(n+1, vector<vector<int>>(m+1, vector<int>(3, 0)));
    maze.resize(n+1, vector<int>(m+1, 0));
    // cost, x, y, color, magic;
    priority_queue<tuple<int, int, int, int, int>, vector<tuple<int, int, int, int, int>>, cmp> heapq;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cin >> maze[i][j];
    heapq.push({0, 1, 1, maze[1][1], 1});
    while(!heapq.empty())
    {
        auto [cost, x, y, color, magic] = heapq.top(); heapq.pop();
        if(x == n && y == m)
        {
            cout << cost << endl;
            return 0;
        }
        if(dp[x][y][color]) continue;
        dp[x][y][color] = 1;
        for(int i = 0; i < 4; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];
            int type = check(nx, ny, color, magic);
            if(!type) continue;
            if(type == 1) heapq.push({cost+0, nx, ny, color, magic});
            if(type == 2) heapq.push({cost+1, nx, ny, maze[nx][ny], magic});
            if(type == 3)
            {
                for(int j = 0; j < 2; j++)
                {
                    int ncolor = (j == 0) ? 1:2;
                    if(!dp[nx][ny][ncolor])
                    {
                        heapq.push({color == ncolor ? cost + 2 : cost + 3, nx, ny, ncolor, 0});
                    }
                }
            }
        }
    }
    cout << -1 << endl;
}