
# P1825 [USACO11OPEN] Corn Maze S

## 题目描述

This past fall, Farmer John took the cows to visit a corn maze. But this wasn't just any corn maze: it featured several gravity-powered teleporter slides, which cause cows to teleport instantly from one point in the maze to another. The slides work in both directions: a cow can slide from the slide's start to the end instantly, or from the end to the start. If a cow steps on a space that hosts either end of a slide, she must use the slide.

The outside of the corn maze is entirely corn except for a single exit.

The maze can be represented by an N x M (2 <= N <= 300; 2 <= M <= 300) grid. Each grid element contains one of these items:

\* Corn (corn grid elements are impassable) 

\* Grass (easy to pass through!) 

\* A slide endpoint (which will transport a cow to the other endpoint) 

\* The exit

A cow can only move from one space to the next if they are adjacent and neither contains corn. Each grassy space has four potential neighbors to which a cow can travel. It takes 1 unit of time to move from a grassy space to an adjacent space; it takes 0 units of time to move from one slide endpoint to the other.

Corn-filled spaces are denoted with an octothorpe (#). Grassy spaces are denoted with a period (.). Pairs of slide endpoints are denoted with the same uppercase letter (A-Z), and no two different slides have endpoints denoted with the same letter. The exit is denoted with the equals sign (=).

Bessie got lost. She knows where she is on the grid, and marked her current grassy space with the 'at' symbol (@). What is the minimum time she needs to move to the exit space?

## 输入格式

Line 1: Two space separated integers: N and M

Lines 2..N+1: Line i+1 describes row i of the maze: M characters (no spaces)

## 输出格式

Line 1: An integer, corresponding to the shortest time that Bessie needs to exit the maze.

## 输入输出样例 #1

### 输入 #1

```
5 6
###=##
#.W.##
#.####
#.@W##
######
```

### 输出 #1

```
3
```

## 说明/提示

例如以下矩阵，$N=5,M=6$。

```plain
###=##
#.W.##
#.####
#.@W##
######
```

唯一的一个装置的结点用大写字母 $\tt{W}$ 表示。

最优方案为：先向右走到装置的结点，花费一个单位时间，再到装置的另一个结点上，花费 $0$ 个单位时间，然后再向右走一个，再向上走一个，到达出口处，总共花费了 $3$ 个单位时间。
## 打算使用广搜, 这是完全臃肿, 且不必要的:
```cpp
#include <bits/stdc++.h>
using namespace std;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
vector<vector<int>> chuansong(26, vector<int>(4, 0));
vector<vector<vector<int>>> mem;
int N, M, x_start, y_start, x_end, y_end;
vector<vecotr<char>> maze;
typedef struct node{
    int cost, x, y, magic;// 0, 1
}node;

struct cmp{
    operator()(const node&a, const node& b){
        return a.cost > b.cost;
    }
};
bool ischuansong(int x, int y)
{
    return maze[x][y] >= 'A' && maze[x][y] <= 'Z';
}
bool check(int x, int y)
{
    return x>=1 && x<=N && y>=1 && y<= M;
}
void chuansong(int& nx, int& ny)
{
    int x1 = chuansong[maze[nx][ny]-'A'][0];
    int y1 = chuansong[maze[nx][ny]-'A'][1];
    int x2 = chuansong[maze[nx][ny]-'A'][2];
    int y2 = chuansong[maze[nx][ny]-'A'][3];
    if(nx == x1 && ny == y1) nx = x2, ny = y2;
    else nx = x1, ny - y1;
}
int main(void)
{
    cin >> N >> M;
    maze.resize(N+1, vector<int>(M+1, '.'));
    mem.resize(N+1, vecotr<vecotr<int>>(M+1, vecot<int>(2, 0)));
    // 第三层数组记录此点是否可以用传送;
    for(int i = 1; i<=N; i++)
    {
        for(int j = 1; j<=M; j++)
        {
            char tempch;
            cin >> tempch;
            if(tempch <= 'Z' && tempch >= 'A')
            {
                chuansong[tempch - 'A'].push_back(i);
                chuansong[tempch - 'A'].push_back(j);
            } 
            if(tempch=='@') x_start = i, y_start = j;
            if(tempch=='=') x_end = i, y_end = j; //这一行似乎可以删掉;
            maze[i][j] = tempch;
        }
    }
    priority_queue<node> heapq;
    heapq.push(0, x_start, y_start, 1)
    while(!haapq.empty())
    {
        auto [cost, x, y, magic_flag] = heapq.top();
        heapq.pop();
        if(x == x_end && y == y_end && maze[x][y] == '=')
        {
            cout << cost << endl;
            return 0;
        }
        if(mem[x][y][flag] != 0) continue;
        mem[x][y][flag] = 1;// 这是自己走来的
        if(ischuansong(x, y) && flag==1) chuansong(x, y), mem[x][y][0] = 1;// 这是自己传来的;
        for(int i = 0; i < 4; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if(!check(nx, ny)) continue;
            if(!mem[nx][ny][flag]==1)
            {
                heapq.push(cost+1, nx, ny, flag);
            }
        } 
    }
}
```
### 下面是AC题解:
```cpp
#include <bits/stdc++.h>
using namespace std;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
map<char, vector<pair<int, int>>> portal;
vector<vector<int>> visited;
vector<vector<char>> maze;
int N, M, x_start, y_start;
//int x_end, y_end;
typedef struct node{
    int cost, x, y;
}node;
struct cmp{
    bool operator()(node a, node b)
    {
        return a.cost > b.cost;
    }
};
bool is_valid(int x, int y)
{
    return x >= 0 && x < N && y >= 0 && y < M && maze[x][y] != '#';
}
bool is_portal(int x, int y)
{
    return maze[x][y] >= 'A' && maze[x][y] <= 'Z';
}

void usePortal(int &nx, int& ny)
{   
    char portal_id = maze[nx][ny];
    auto &points = portal[portal_id];
    if(nx == points[0].first && ny == points[0].second)
    {
        nx = points[1].first;
        ny = points[1].second;
    }
    else
    {
        nx = points[0].first;
        ny = points[0].second;
    }
}

int main(void)
{
    cin >> N >> M;
    visited.resize(N, vector<int>(M, 0));
    maze.resize(N, vector<char>(M, 0));
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            cin >> maze[i][j];
            if(is_portal(i, j))
            {
                portal[maze[i][j]].push_back({i, j});
            }
            if(maze[i][j] == '@') x_start = i, y_start = j;
        }
    }
    priority_queue<node, vector<node>, cmp> heapq;
    heapq.push({0, x_start, y_start});
    while(!heapq.empty())
    {
        auto [cost, x, y] = heapq.top();
        heapq.pop();
        if(visited[x][y]) continue;
        visited[x][y] = 1;
        if(maze[x][y] == '=')
        {
            cout << cost << endl;
            return 0;
        }
        for(int i = 0; i < 4; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if(is_portal(nx, ny)) usePortal(nx, ny);
            if(is_valid(nx, ny) && !visited[nx][ny])
            {
                heapq.push({cost + 1, nx, ny});
            }
        }
    }
    cout << -1 << endl;
    return 0;
}
```
