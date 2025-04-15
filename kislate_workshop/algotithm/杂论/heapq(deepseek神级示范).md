## deepseek的`Dijkstra 算法`神级示范，充分利用`heapq`的优先性质
```python
import heapq

m, n = map(int, input().split())

# 初始化棋盘，1-based索引
grid = [[-1] * (m + 2) for _ in range(m + 2)]
for _ in range(n):
    x, y, c = map(int, input().split())
    grid[x][y] = c

# 初始化 visited 数组，visited[x][y][last_color][can_use]
visited = [[[[False] * 2 for _ in range(2)] for __ in range(m + 2)] for ___ in range(m + 2)]

start_color = grid[1][1]
heap = []
heapq.heappush(heap, (0, 1, 1, start_color, 1))  # (cost, x, y, last_color, can_use)

directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

found = False
while heap:
    cost, x, y, last_color, can_use = heapq.heappop(heap)
    if x == m and y == m:
        print(cost)
        found = True
        break
    if visited[x][y][last_color][can_use]:
        continue
    visited[x][y][last_color][can_use] = True  # 标记为已访问
    for dx, dy in directions:
        nx, ny = x + dx, y + dy
        if 1 <= nx <= m and 1 <= ny <= m:
            if grid[nx][ny] != -1:
                # 目标格子有颜色
                new_color = grid[nx][ny]
                new_cost = cost + (0 if last_color == new_color else 1)
                new_can_use = 1  # 移动到有颜色格子后，可以再次使用魔法
                if not visited[nx][ny][new_color][new_can_use]:
                    heapq.heappush(heap, (new_cost, nx, ny, new_color, new_can_use))
            else:
                # 目标格子无色，需要施法
                if can_use:
                    # 尝试两种颜色选择
                    for new_color in [0, 1]:
                        cost_change = 2
                        if new_color != last_color:
                            cost_change += 1
                        new_cost = cost + cost_change
                        new_can_use = 0  # 使用魔法后不能立即再次使用
                        if not visited[nx][ny][new_color][new_can_use]:
                            heapq.heappush(heap, (new_cost, nx, ny, new_color, new_can_use))

if not found:
    print(-1)
```

### 实际上更加完整的Dijkstra是不断记录不断更新到达每一个点的最短路径：
- 在`Dijkstra`中就应该没有那个已经达到终点就`break`的条件
- 这样就会遍历每一个点
```python
import heapq

# 初始化距离数组，dist[x][y][last_color][can_use]
dist = [[[[INF] * 2 for _ in range(2)] for __ in range(m + 2)] for ___ in range(m + 2)]
#


found = False
while heap:
    cost, x, y, last_color, can_use = heapq.heappop(heap)
    if cost > dist[x][y][last_color][can_use]:# 判断是否更小
        continue
    for dx, dy in directions:
        nx, ny = x + dx, y + dy
        if 1 <= nx <= m and 1 <= ny <= m:
            if grid[nx][ny] != -1:
                # 目标格子有颜色
                new_color = grid[nx][ny]
                new_cost = cost + (0 if last_color == new_color else 1)
                new_can_use = 1  # 移动到有颜色格子后，可以再次使用魔法
                if new_cost < dist[nx][ny][new_color][new_can_use]:#判断
                    dist[nx][ny][new_color][new_can_use] = new_cost
                    heapq.heappush(heap, (new_cost, nx, ny, new_color, new_can_use))
            else:
              #
if not found:
    print(-1)
```

#### 这里有一个C++的实现范例：

```c++
#include <iostream>
#include <queue>
#include <vector>
#include <climits>
using namespace std;

struct Node {
    int cost, x, y, last_color, can_use;
    Node(int c, int x_, int y_, int lc, int cu) 
        : cost(c), x(x_), y(y_), last_color(lc), can_use(cu) {}
    bool operator>(const Node& other) const { return cost > other.cost; }
};

int main() {
    int m, n;
    cin >> m >> n;

    // 初始化棋盘（1-based索引）
    vector<vector<int>> board(m + 2, vector<int>(m + 2, -1));
    for (int i = 0; i < n; ++i) {
        int x, y, c;
        cin >> x >> y >> c;
        board[x][y] = c;
    }

    // 方向数组：上下左右
    const int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

    // 访问标记：mem[x][y][color][can_use]
    vector<vector<vector<vector<bool>>>> mem(
        m + 2, vector<vector<vector<bool>>>(
            m + 2, vector<vector<bool>>(
                2, vector<bool>(2, false))));

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    int start_color = board[1][1];
    pq.emplace(0, 1, 1, start_color, 1);

    bool found = false;
    while (!pq.empty()) {
        auto [cost, x, y, lc, cu] = pq.top();
        pq.pop();

        if (x == m && y == m) {
            cout << cost << endl;
            found = true;
            break;
        }

        if (mem[x][y][lc][cu]) continue;
        mem[x][y][lc][cu] = true;

        for (auto [dx, dy] : dirs) {
            int nx = x + dx, ny = y + dy;
            if (nx < 1 || nx > m || ny < 1 || ny > m) continue;

            if (board[nx][ny] != -1) { // 目标格子有颜色
                int new_color = board[nx][ny];
                int new_cost = cost + (lc == new_color ? 0 : 1);
                if (!mem[nx][ny][new_color][1])
                    pq.emplace(new_cost, nx, ny, new_color, 1);
            } else if (cu) { // 使用魔法
                for (int color : {0, 1}) {
                    int new_cost = cost + 2 + (lc != color ? 1 : 0);
                    if (!mem[nx][ny][color][0])
                        pq.emplace(new_cost, nx, ny, color, 0);
                }
            }
        }
    }

    if (!found) cout << -1 << endl;
    return 0;
}
```


## 以下是一个`最大堆`的实现方式：
在 Python 中，`heapq` 模块默认实现的是最小堆（min-heap），这意味着你每次从堆中弹出的元素都是当前堆中最小的元素。如果你想实现最大堆（max-heap），可以通过将元素的值取负数来实现。

以下是一个示例，展示了如何使用 `heapq` 模块实现最大堆：

```python
import heapq

# 创建一个空的最大堆
max_heap = []

# 向最大堆中插入元素
heapq.heappush(max_heap, -1 * 10)
heapq.heappush(max_heap, -1 * 20)
heapq.heappush(max_heap, -1 * 5)

# 从最大堆中弹出元素
print(-1 * heapq.heappop(max_heap))  # 输出 20
print(-1 * heapq.heappop(max_heap))  # 输出 10
print(-1 * heapq.heappop(max_heap))  # 输出 5
```

在这个示例中，我们将元素的值取负数，然后使用 `heapq.heappush` 将其插入堆中。弹出元素时，再将其值取负数，以恢复原始值。

对于你的问题，可以使用 `heapq` 模块实现最大堆来解决技能冷却时间的问题。以下是一个示例代码，展示了如何使用 `heapq` 模块实现最大堆，并解决技能冷却时间的问题：

```python
import heapq

def minimize_max_cooldown(n, m, k, skills):
    # 创建一个最大堆
    max_heap = []
    
    # 将技能的冷却时间和升级所需技能点插入最大堆
    for t, c in skills:
        heapq.heappush(max_heap, (-t, c))
    
    # 使用技能点减少冷却时间
    while m > 0 and max_heap:
        t, c = heapq.heappop(max_heap)
        t = -t
        if t > k:
            # 计算可以减少的冷却时间
            reduce_time = min(t - k, m // c)
            t -= reduce_time
            m -= reduce_time * c
            heapq.heappush(max_heap, (-t, c))
        else:
            heapq.heappush(max_heap, (-t, c))
            break
    
    # 返回最大堆中的最大冷却时间
    return -max_heap[0][0]

# 示例输入
n = 4
m = 9
k = 2
skills = [(6, 1), (5, 1), (6, 2), (7, 1)]

# 计算最小化的冷却时间的最大值
result = minimize_max_cooldown(n, m, k, skills)
print(result)  # 输出 5
```

在这个示例中，我们使用 `heapq` 模块实现最大堆，并通过使用技能点减少冷却时间来最小化冷却时间的最大值。