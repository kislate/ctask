`deque` 是 Python 标准库 `collections` 模块中的双端队列（double-ended queue），它提供了在两端快速添加和删除元素的功能。`deque` 是一个通用的容器，可以用作栈、队列和双端队列。

### 导入 `deque`
首先，你需要从 `collections` 模块中导入 `deque`：
```python
from collections import deque
```

### 创建 `deque`
你可以通过以下方式创建一个 `deque`：
```python
# 创建一个空的 deque
dq = deque()

# 创建一个包含初始元素的 deque
dq = deque([1, 2, 3, 4])
```

### 常用方法
以下是 `deque` 的一些常用方法：

1. **`append(x)`**：在右端添加元素 `x`。
   ```python
   dq.append(5)
   print(dq)  # 输出: deque([1, 2, 3, 4, 5])
   ```

2. **`appendleft(x)`**：在左端添加元素 `x`。
   ```python
   dq.appendleft(0)
   print(dq)  # 输出: deque([0, 1, 2, 3, 4, 5])
   ```

3. **`pop()`**：移除并返回右端的元素。
   ```python
   dq.pop()
   print(dq)  # 输出: deque([0, 1, 2, 3, 4])
   ```

4. **`popleft()`**：移除并返回左端的元素。
   ```python
   dq.popleft()
   print(dq)  # 输出: deque([1, 2, 3, 4])
   ```

5. **`extend(iterable)`**：在右端添加多个元素。
   ```python
   dq.extend([5, 6, 7])
   print(dq)  # 输出: deque([1, 2, 3, 4, 5, 6, 7])
   ```

6. **`extendleft(iterable)`**：在左端添加多个元素（注意添加顺序）。
   ```python
   dq.extendleft([0, -1, -2])
   print(dq)  # 输出: deque([-2, -1, 0, 1, 2, 3, 4, 5, 6, 7])
   ```

7. **`rotate(n)`**：旋转 `deque`，将右端的 `n` 个元素移动到左端。如果 `n` 为负数，则将左端的 `n` 个元素移动到右端。
   ```python
   dq.rotate(2)
   print(dq)  # 输出: deque([6, 7, -2, -1, 0, 1, 2, 3, 4, 5])
   dq.rotate(-2)
   print(dq)  # 输出: deque([-2, -1, 0, 1, 2, 3, 4, 5, 6, 7])
   ```

8. **`clear()`**：清空 `deque`。
   ```python
   dq.clear()
   print(dq)  # 输出: deque([])
   ```

### 示例代码
以下是一个使用 `deque` 实现广度优先搜索（BFS）的示例代码：

```python
from collections import deque

def bfs(graph, start):
    visited = set()
    queue = deque([start])
    visited.add(start)

    while queue:
        vertex = queue.popleft()
        print(vertex, end=" ")

        for neighbor in graph[vertex]:
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)

# 示例图的邻接表表示
graph = {
    1: [2, 3],
    2: [4, 5],
    3: [6],
    4: [],
    5: [],
    6: []
}

# 从节点1开始进行BFS
bfs(graph, 1)
```

### 输出
```
1 2 3 4 5 6
```

在这个示例中，`deque` 用于实现 BFS 算法的队列，确保在遍历图时能够高效地添加和移除节点。

找到具有 1 个许可证类型的类似代码