# P1596 [USACO10OCT] Lake Counting S

## 题目描述
$$luogu不给翻译$$
Due to recent rains, water has pooled in various places in Farmer John's field, which is represented by a rectangle of N x M (1 <= N <= 100; 1 <= M <= 100) squares. Each square contains either water ('W') or dry land ('.'). Farmer John would like to figure out how many ponds have formed in his field. A pond is a connected set of squares with water in them, where a square is considered adjacent to all eight of its neighbors. Given a diagram of Farmer John's field, determine how many ponds he has.

## 输入格式

Line 1: Two space-separated integers: N and M \* Lines 2..N+1: M characters per line representing one row of Farmer John's field. Each character is either 'W' or '.'. The characters do not have spaces between them.

## 输出格式

Line 1: The number of ponds in Farmer John's field.

## 输入输出样例 #1

### 输入 #1

```
10 12
W........WW.
.WWW.....WWW
....WW...WW.
.........WW.
.........W..
..W......W..
.W.W.....WW.
W.W.W.....W.
.W.W......W.
..W.......W.
```

### 输出 #1

```
3
```

## 说明/提示

OUTPUT DETAILS: There are three ponds: one in the upper left, one in the lower left, and one along the right side.
## AC:
```cpp
#include <bits/stdc++.h>
using namespace std;
int dx[8] = {0, 0, 1, 1, 1, -1, -1, -1};
int dy[8] = {1, -1, 0, 1, -1, 1, -1, 0};
int N, M, cnt = 0;
vector<vector<char>> water;
queue<pair<int, int>> heap;
vector<vector<int>> mem; // 打算一就是已经探索过了的, 不需要再探索了;
bool check(int x, int y);
void bfs();
int main(void)
{
    cin >> N >> M;
    water.resize(N+1, vector<char>(M+1, '.'));
    mem.resize(N+1, vector<int>(M+1, 0));
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            cin >> water[i][j];
        }
    }
    for(int i = 1; i<=N; i++)
    {
        for(int j = 1; j<=M; j++)
        {
            if(water[i][j] == 'W' && mem[i][j] != 1)
            {
                // mem[i][j] = 1;
                heap.push({i, j});
                bfs();
                cnt++;
            }
        }
    }
    cout << cnt << endl;
}
void bfs()
{
    while(!heap.empty())
    {
        auto [x, y] = heap.front();
        heap.pop();
        if(!check(x, y) || water[x][y] == '.' || mem[x][y])// 如果不在边界内, 是干旱, 或者已经来过了
            continue;
        mem[x][y] = 1;
        for(int i = 0; i < 8; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            heap.push({nx, ny});
        }
    }
    // while(!heap.empty())
    // {
    //     auto [x, y] = heap.front();
    //     heap.pop();
    //     for(int i = 0; i < 8; i++)
    //     {
    //         int nx = x + dx[i];
    //         int ny = y + dy[i];
    //         if(!check(nx, ny) || water[nx][ny] == '.' || mem[nx][ny])// 如果不在边界内, 是干旱, 或者已经来过了
    //             continue;
    //         mem[nx][ny] = 1;
    //         heap.push({nx, ny});
    //     }
    // }
}

bool check(int x, int y)
{
    return (x>=1 && x<=N && y>=1 && y<=M);
}
```