在 C++ 中，可以使用标准库中的 `priority_queue` 来实现最大堆和最小堆。默认情况下，`priority_queue` 实现的是最大堆，但可以通过自定义比较函数来实现最小堆。

### 最大堆

默认情况下，`priority_queue` 实现的是最大堆。以下是一个示例，展示了如何使用 `priority_queue` 实现最大堆：

```cpp
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    // 创建一个最大堆
    priority_queue<int> max_heap;

    // 向最大堆中插入元素
    max_heap.push(10);
    max_heap.push(20);
    max_heap.push(5);

    // 从最大堆中弹出元素
    cout << max_heap.top() << endl; // 输出 20
    max_heap.pop();
    cout << max_heap.top() << endl; // 输出 10
    max_heap.pop();
    cout << max_heap.top() << endl; // 输出 5
    max_heap.pop();

    return 0;
}
```

### 最小堆

可以通过自定义比较函数来实现最小堆。以下是一个示例，展示了如何使用 `priority_queue` 实现最小堆：

```cpp
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    // 创建一个最小堆
    priority_queue<int, vector<int>, greater<int>> min_heap;

    // 向最小堆中插入元素
    min_heap.push(10);
    min_heap.push(20);
    min_heap.push(5);

    // 从最小堆中弹出元素
    cout << min_heap.top() << endl; // 输出 5
    min_heap.pop();
    cout << min_heap.top() << endl; // 输出 10
    min_heap.pop();
    cout << min_heap.top() << endl; // 输出 20
    min_heap.pop();

    return 0;
}
```

在 C++ 中，`priority_queue` 是一个模板类，用于实现优先队列。默认情况下，`priority_queue` 实现的是最大堆（max-heap），即优先队列中最大的元素具有最高优先级。然而，通过自定义比较函数，可以将 `priority_queue` 转换为最小堆（min-heap）。

`priority_queue<int, vector<int>, greater<int>> min_heap;` 这行代码的意思是创建一个存储 `int` 类型元素的最小堆。具体来说：

- `int`：表示优先队列中存储的元素类型为 `int`。
- `vector<int>`：表示底层容器使用 `vector<int>`，即使用 `std::vector` 来存储元素。
- `greater<int>`：表示使用 `std::greater<int>` 作为比较函数，从而将 `priority_queue` 转换为最小堆。

### 自定义结构体的最小堆

如果需要在堆中存储自定义结构体，可以通过重载比较运算符或提供自定义比较函数来实现。以下是一个示例，展示了如何在堆中存储自定义结构体：

```cpp
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    int cost;
    int x, y;
    Node(int c, int x_, int y_) : cost(c), x(x_), y(y_) {}
    bool operator<(const Node& other) const {
        return cost > other.cost; // 实现最小堆
    }
};

int main() {
    // 创建一个最小堆
    priority_queue<Node> min_heap;

    // 向最小堆中插入元素
    min_heap.emplace(10, 1, 1);
    min_heap.emplace(20, 2, 2);
    min_heap.emplace(5, 0, 0);

    // 从最小堆中弹出元素
    cout << min_heap.top().cost << endl; // 输出 5
    min_heap.pop();
    cout << min_heap.top().cost << endl; // 输出 10
    min_heap.pop();
    cout << min_heap.top().cost << endl; // 输出 20
    min_heap.pop();

    return 0;
}
```

在这个示例中，我们定义了一个 `Node` 结构体，并重载了 `<` 运算符，以实现最小堆。通过这种方式，可以在堆中存储自定义结构体，并根据自定义的比较规则进行排序。

### 自定义结构体的堆

如果需要在堆中存储自定义结构体，可以通过重载比较运算符或提供自定义比较函数来实现。以下是一个示例，展示了如何在堆中存储自定义结构体：

```cpp
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
    int cost;
    int x, y;
    Node(int c, int x_, int y_) : cost(c), x(x_), y(y_) {}
    bool operator<(const Node& other) const {
        return cost > other.cost; // 实现最小堆
    }
};

int main() {
    // 创建一个最小堆
    priority_queue<Node> min_heap;

    // 向最小堆中插入元素
    min_heap.emplace(10, 1, 1);
    min_heap.emplace(20, 2, 2);
    min_heap.emplace(5, 0, 0);

    // 从最小堆中弹出元素
    cout << min_heap.top().cost << endl; // 输出 5
    min_heap.pop();
    cout << min_heap.top().cost << endl; // 输出 10
    min_heap.pop();
    cout << min_heap.top().cost << endl; // 输出 20
    min_heap.pop();

    return 0;
}
```

在这个示例中，我们定义了一个 `Node` 结构体，并重载了 `<` 运算符，以实现最小堆。通过这种方式，可以在堆中存储自定义结构体，并根据自定义的比较规则进行排序。