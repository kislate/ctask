在 C++ 中，`queue` 是标准模板库（STL）中的一个容器适配器，它提供了先进先出（FIFO）的数据结构。`queue` 允许在一端（尾部）添加元素，在另一端（头部）移除元素。它是一个非常有用的数据结构，特别适用于广度优先搜索（BFS）等算法。

### 导入 `queue`
要使用 `queue`，你需要包含头文件 `<queue>`：
```cpp
#include <queue>
```

### 创建 `queue`
你可以通过以下方式创建一个 `queue`：
```cpp
#include <queue>
#include <iostream>

using namespace std;

int main() {
    // 创建一个空的 queue
    queue<int> q;

    // 检查 queue 是否为空
    if (q.empty()) {
        cout << "Queue is empty" << endl;
    }

    return 0;
}
```

### 常用方法
以下是 `queue` 的一些常用方法：

1. **`push(const T& value)`**：在队列的尾部添加一个元素。
   ```cpp
   q.push(10);
   ```

2. **`pop()`**：移除队列头部的元素。
   ```cpp
   q.pop();
   ```

3. **`front()`**：返回队列头部的元素。
   ```cpp
   int front = q.front();
   ```

4. **`back()`**：返回队列尾部的元素。
   ```cpp
   int back = q.back();
   ```

5. **`empty()`**：检查队列是否为空。
   ```cpp
   if (q.empty()) {
       cout << "Queue is empty" << endl;
   }
   ```

6. **`size()`**：返回队列中的元素数量。
   ```cpp
   cout << "Queue size: " << q.size() << endl;
   ```

### 示例代码
以下是一个使用 `queue` 的示例代码，展示了如何在队列中添加和移除元素：

```cpp
#include <queue>
#include <iostream>

using namespace std;

int main() {
    queue<int> q;

    // 在队列中添加元素
    q.push(1);
    q.push(2);
    q.push(3);

    // 输出队列的头部和尾部元素
    cout << "Front element: " << q.front() << endl;  // 输出: 1
    cout << "Back element: " << q.back() << endl;    // 输出: 3

    // 移除队列的头部元素
    q.pop();
    cout << "Front element after pop: " << q.front() << endl;  // 输出: 2

    // 输出队列的大小
    cout << "Queue size: " << q.size() << endl;  // 输出: 2

    return 0;
}
```

### 在你的代码中
在你的代码中，你使用了 `queue` 来实现广度优先搜索（BFS），以下是完整的代码和解释：

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);  // 禁用同步，加速输入输出
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> tasks(n + 1);  // 前置任务列表

    // 读取输入
    for (int i = 1; i <= n; ++i) {
        int ci;
        cin >> ci;
        tasks[i].resize(ci);
        for (int j = 0; j < ci; ++j) {
            cin >> tasks[i][j];
        }
    }

    vector<bool> visited(n + 1, false);
    queue<int> q;
    int count = 1;  // 包含任务1

    q.push(1);
    visited[1] = true;

    // BFS 遍历
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        for (int p : tasks[current]) {
            if (!visited[p]) {
                visited[p] = true;
                count++;
                q.push(p);
            }
        }
    }

    cout << count << endl;
    return 0;
}
```

### 代码解释
1. **导入头文件**：
   ```cpp
   #include <iostream>
   #include <vector>
   #include <queue>
   ```

2. **读取任务数量 `n`**：
   ```cpp
   int n;
   cin >> n;
   ```

3. **初始化任务列表 `tasks`**：
   ```cpp
   vector<vector<int>> tasks(n + 1);
   ```

4. **读取输入数据**：
   ```cpp
   for (int i = 1; i <= n; ++i) {
       int ci;
       cin >> ci;
       tasks[i].resize(ci);
       for (int j = 0; j < ci; ++j) {
           cin >> tasks[i][j];
       }
   }
   ```

5. **初始化 `visited` 向量和 `queue`**：
   ```cpp
   vector<bool> visited(n + 1, false);
   queue<int> q;
   int count = 1;  // 包含任务1
   ```

6. **将任务1添加到队列并标记为已访问**：
   ```cpp
   q.push(1);
   visited[1] = true;
   ```

7. **BFS 遍历**：
   ```cpp
   while (!q.empty()) {
       int current = q.front();
       q.pop();
       for (int p : tasks[current]) {
           if (!visited[p]) {
               visited[p] = true;
               count++;
               q.push(p);
           }
       }
   }
   ```

8. **输出结果**：
   ```cpp
   cout << count << endl;
   ```

这个代码使用 `queue` 来实现广度优先搜索，计算完成任务1所需的最少任务数量。