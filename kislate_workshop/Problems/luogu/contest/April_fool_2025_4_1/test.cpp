/*
    author: 0x3f3f3f3f
    date: 2025-04-01 20:00:00
    problem: luogu P2895
*/
// 这题有点意思
#include <bits/stdc++.h>
using namespace std;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
typedef struct {
    int cost, x, y;
} node;
struct cmp{
    bool operator()(const node &a, const node &b) const{
        return a.cost > b.cost;
    }
};
int M;
vector<vector<int>> damage_time(1000, vector<int>(1000, 1e9));
vector<vector<int>> mem(1000, vector<int>(1000, 0));
int main(void)
{
    cin >> M;
    priority_queue<node, vector<node>, cmp> heapq;
    for(int i = 0; i < M; i++)
    {
        int tempx, tempy, damagetime;
        cin >> tempx >> tempy >> damagetime;
        damage_time[tempx][tempy] = min(damage_time[tempx][tempy], damagetime);
        for(int j = 0; j < 4; j++)
        {
            int newx = tempx + dx[j];
            int newy = tempy + dy[j];
            if(newx >= 0 && newx < 1000 && newy >= 0 && newy < 1000)
            {
                damage_time[newx][newy] = min(damage_time[newx][newy], damagetime);
            }
        }
    }
    mem[0][0] = 1;
    heapq.push({0, 0, 0});
    while(!heapq.empty())// dijkstra
    {
        node now = heapq.top();
        heapq.pop();
        int x = now.x, y = now.y, cost = now.cost;
        if(mem[x][y] == 1 || x < 0 || x >= 1000 || y < 0 || y >= 1000)
            continue;
        mem[x][y] = 1;
        if(damage_time[x][y] == 1e9)
        {
            cout << cost << endl;
            return 0;
        }
        for(int i = 0; i < 4; i++)
        {
            int nx = x+dx[i], ny = y+dy[i], ncost = cost + 1;
            if(nx < 0 || nx >= 1000 || ny < 0 || ny >= 1000)
                continue;
            if(mem[nx][ny] == 1)
                continue;
            if(ncost >= damage_time[nx][ny])
                continue;
            heapq.push({ncost, nx, ny});
        }
    }
    cout << -1 << endl;
    return 0;
}
