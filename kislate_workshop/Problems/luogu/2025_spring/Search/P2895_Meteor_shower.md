# P2895 [USACO08FEB] Meteor Shower S

## 题目描述

贝茜听说一场特别的流星雨即将到来：这些流星会撞向地球，并摧毁它们所撞击的任何东西。她为自己的安全感到焦虑，发誓要找到一个安全的地方（一个永远不会被流星摧毁的地方）。

如果将牧场放入一个直角坐标系中，贝茜现在的位置是原点，并且，贝茜不能踏上一块被流星砸过的土地。

根据预报，一共有 $M$ 颗流星 $(1\leq M\leq 50,000)$ 会坠落在农场上，其中第 $i$ 颗流星会在时刻 $T_i$（$0 \leq T _ i \leq 1000$）砸在坐标为 $(X_i,Y_i)(0\leq X_i\leq 300$，$0\leq Y_i\leq 300)$ 的格子里。流星的力量会将它所在的格子，以及周围 $4$ 个相邻的格子都化为焦土，当然贝茜也无法再在这些格子上行走。

贝茜在时刻 $0$ 开始行动，她只能在会在横纵坐标 $X,Y\ge 0$ 的区域中，平行于坐标轴行动，每 $1$ 个时刻中，她能移动到相邻的（一般是 $4$ 个）格子中的任意一个，当然目标格子要没有被烧焦才行。如果一个格子在时刻 $t$ 被流星撞击或烧焦，那么贝茜只能在 $t$ 之前的时刻在这个格子里出现。 贝茜一开始在 $(0,0)$。

请你计算一下，贝茜最少需要多少时间才能到达一个安全的格子。如果不可能到达输出 $−1$。

## 输入格式

共 $M+1$ 行，第 $1$ 行输入一个整数 $M$，接下来的 $M$ 行每行输入三个整数分别为 $X_i, Y_i, T_i$。

## 输出格式

贝茜到达安全地点所需的最短时间，如果不可能，则为 $-1$。

## 输入输出样例 #1

### 输入 #1

```
4
0 0 2
2 1 2
1 1 2
0 3 5
```

### 输出 #1

```
5
```
## 我的错误代码:
```cpp
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
    mem[0][0] = 1;// 这行删掉就对了.
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
```
### copilot的改正代码:
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1000;
const int MAX_TIME = 1e9;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

struct node {
    int cost, x, y;
};

struct cmp {
    bool operator()(const node &a, const node &b) const {
        return a.cost > b.cost;
    }
};

bool check(int x, int y) {
    return x >= 0 && x < MAX_N && y >= 0 && y < MAX_N;
}

int main(void) {
    int M;
    cin >> M;
    
    if(M <= 0 || M > 50000) {
        cout << -1 << endl;
        return 0;
    }

    vector<vector<int>> damage_time(MAX_N, vector<int>(MAX_N, MAX_TIME));
    vector<vector<int>> mem(MAX_N, vector<int>(MAX_N, 0));
    priority_queue<node, vector<node>, cmp> heapq;

    // 处理流星落点
    for(int i = 0; i < M; i++) {
        int tempx, tempy, damagetime;
        cin >> tempx >> tempy >> damagetime;
        damage_time[tempx][tempy] = min(damage_time[tempx][tempy], damagetime);
        
        // 处理周围格子
        for(int j = 0; j < 4; j++) {
            int newx = tempx + dx[j];
            int newy = tempy + dy[j];
            if(check(newx, newy)) {
                damage_time[newx][newy] = min(damage_time[newx][newy], damagetime);
            }
        }
    }

    // Dijkstra算法寻找安全点
    mem[0][0] = 1;
    heapq.emplace(node{0, 0, 0});

    while(!heapq.empty()) {
        auto [cost, x, y] = heapq.top();
        heapq.pop();

        if(!check(x, y) || mem[x][y] >1) continue;
        
        if(damage_time[x][y] == MAX_TIME) {
            cout << cost << endl;
            return 0;
        }

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i], ncost = cost + 1;
            if(!check(nx, ny) || mem[nx][ny] || ncost >= damage_time[nx][ny]) continue;
            mem[nx][ny] = 1;
            heapq.emplace(node{ncost, nx, ny});
        }
    }

    cout << -1 << endl;
    return 0;
}
```

