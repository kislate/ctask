#include <bits/stdc++.h>
using namespace std;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int n, m;
struct cmp{
    // tuple;
    bool operator()(tuple<int, int, int, int, int> a, tuple<int, int, int, int, int> b)
    {
        return get<0>(a) > get<0>(b);
    }
};
bool check(int nx, int ny)
{
    if(nx < 1 || nx > m || ny < 1 || ny > m) return false;
    return true;
}
vector<vector<int>> maze;
vector<vector<vector<vector<bool>>>> visited;
int main(void)
{
    cin >> m >> n;
    //  visited[i][j][color][magic] = false;                                                                                                                            
    visited.resize(m + 1, vector<vector<vector<bool>>>(m + 1, vector<vector<bool>>(2, vector<bool>(2, false))));
    maze.resize(m + 1, vector<int>(m + 1, -1));
    priority_queue<tuple<int, int, int, int, int>, vector<tuple<int, int, int, int, int>>, cmp> heapq;
    for(int i = 0; i < n; i++)
    {
        int x, y, color;
        cin >> x >> y >> color;
        maze[x][y] = color;
    }
    heapq.push({0, 1, 1, maze[1][1], 1});// cost, x, y, color, magic
    while(!heapq.empty())
    {
        auto [cost, x, y, color, magic] = heapq.top();
        heapq.pop();
        if(visited[x][y][color][magic]) continue;
        visited[x][y][color][magic] = true;
        if(x == m && y == m){
            cout << cost << endl;
            return 0;
        }
        for(int i = 0; i < 4; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if(!check(nx, ny)) continue;
            int ncolor = maze[nx][ny];
            if(ncolor == 1 || ncolor == 0)
            {
                int dcost = color == ncolor ? 0 : 1;
                if(!visited[nx][ny][ncolor][magic])
                {
                    heapq.push({cost + dcost, nx, ny, ncolor, 1});
                }
            }
            else
            {
                if(magic == 0) continue;
                for(int j = 0; j < 2; j++)
                {
                    int tmp_color = j;
                    int dcost = color == tmp_color ? 2 : 3;
                    if(!visited[nx][ny][tmp_color][magic - 1])
                    {
                        heapq.push({cost + dcost, nx, ny, tmp_color, magic - 1});
                    }
                }
            }
        }
    }
    cout << -1 << endl;
}