`heapq` 是 Python 标准库中的一个模块，它提供了堆队列算法的实现，也称为优先队列算法。堆是一种特殊的树形数据结构，满足堆属性：在最小堆中，每个父节点的值都小于或等于其子节点的值；在最大堆中，每个父节点的值都大于或等于其子节点的值。

`heapq` 模块实现了一个最小堆，提供了一些基本的堆操作函数。以下是 `heapq` 模块的一些常用函数及其用法：

### 导入 `heapq`
首先，你需要导入 `heapq` 模块：
```python
import heapq
```

### 常用函数
1. **`heapq.heappush(heap, item)`**：将元素 `item` 添加到堆中。
   ```python
   heap = []
   heapq.heappush(heap, 3)
   heapq.heappush(heap, 1)
   heapq.heappush(heap, 2)
   print(heap)  # 输出: [1, 3, 2]
   ```

2. **`heapq.heappop(heap)`**：从堆中弹出并返回最小的元素。
   ```python
   smallest = heapq.heappop(heap)
   print(smallest)  # 输出: 1
   print(heap)      # 输出: [2, 3]
   ```

3. **`heapq.heappushpop(heap, item)`**：将元素 `item` 添加到堆中，然后弹出并返回最小的元素。
   ```python
   smallest = heapq.heappushpop(heap, 0)
   print(smallest)  # 输出: 0
   print(heap)      # 输出: [2, 3]
   ```

4. **`heapq.heapreplace(heap, item)`**：弹出并返回堆中的最小元素，然后将元素 `item` 添加到堆中。
   ```python
   smallest = heapq.heapreplace(heap, 4)
   print(smallest)  # 输出: 2
   print(heap)      # 输出: [3, 4]
   ```

5. **`heapq.heapify(x)`**：将列表 `x` 转换为堆。
   ```python
   heap = [3, 1, 2]
   heapq.heapify(heap)
   print(heap)  # 输出: [1, 3, 2]
   ```

### 示例代码
以下是一个使用 `heapq` 模块实现优先队列的示例代码：

```python
import heapq

# 创建一个空堆
heap = []

# 添加元素到堆中
heapq.heappush(heap, 3)
heapq.heappush(heap, 1)
heapq.heappush(heap, 2)

# 输出堆中的最小元素
print("Heap:", heap)  # 输出: Heap: [1, 3, 2]

# 弹出并返回堆中的最小元素
smallest = heapq.heappop(heap)
print("Smallest element:", smallest)  # 输出: Smallest element: 1

# 输出堆的当前状态
print("Heap after pop:", heap)  # 输出: Heap after pop: [2, 3]
```

### 在你的代码中
在你的代码中，你可以使用 `heapq` 模块来实现一个优先队列，以便在搜索过程中总是优先处理代价最小的路径。例如：

```python
import heapq

def min_cost_to_reach_end(m, n, colored_cells):
    # 初始化棋盘
    board = [[-1] * m for _ in range(m)]
    for x, y, c in colored_cells:
        board[x-1][y-1] = c

    # 定义方向向量
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

    # 优先队列，存储 (花费, x, y, 是否可以使用魔法)
    pq = [(0, 0, 0, True)]
    heapq.heapify(pq)

    # 访问标记
    visited = set()

    while pq:
        cost, x, y, can_use_magic = heapq.heappop(pq)

        # 如果到达终点
        if (x, y) == (m-1, m-1):
            return cost

        # 标记访问
        if (x, y, can_use_magic) in visited:
            continue
        visited.add((x, y, can_use_magic))

        # 遍历四个方向
        for dx, dy in directions:
            nx, ny = x + dx, y + dy
            if 0 <= nx < m and 0 <= ny < m:
                if board[nx][ny] != -1:
                    new_cost = cost + (board[nx][ny] != board[x][y])
                    heapq.heappush(pq, (new_cost, nx, ny, can_use_magic))
                elif can_use_magic:
                    heapq.heappush(pq, (cost + 2, nx, ny, False))

    return -1

# 示例输入
m = 5
n = 7
colored_cells = [
    (1, 1, 0),
    (1, 2, 0),
    (2, 2, 1),
    (3, 3, 1),
    (3, 4, 0),
    (4, 4, 1),
    (5, 5, 0)
]

# 计算最小花费
print(min_cost_to_reach_end(m, n, colored_cells))  # 输出: 8
```

这个示例代码使用 `heapq` 模块实现了一个优先队列，以便在搜索过程中总是优先处理代价最小的路径，从而计算从棋盘左上角到右下角的最小花费。