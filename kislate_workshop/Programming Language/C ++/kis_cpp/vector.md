在C++中，`vector`是标准模板库（STL）中的一个容器类，用于存储动态数组。与普通数组不同，`vector`可以根据需要自动调整其大小，并且提供了许多方便的成员函数来操作其中的元素。

以下是一些关于`vector`的基本信息和常用操作：

### 声明和初始化

```cpp
#include <vector>
using namespace std;

vector<int> v1; // 创建一个空的int类型的vector
vector<int> v2(10); // 创建一个包含10个元素的int类型的vector，所有元素初始化为0
vector<int> v3(10, 5); // 创建一个包含10个元素的int类型的vector，所有元素初始化为5
vector<int> v4 = {1, 2, 3, 4, 5}; // 使用列表初始化
```

### 常用操作

- **添加元素**：使用`push_back`函数在`vector`的末尾添加元素。
    ```cpp
    v1.push_back(1); // 在v1的末尾添加元素1
    ```

- **访问元素**：使用下标运算符`[]`或`at`函数访问元素。
    ```cpp
    int x = v1[0]; // 访问v1的第一个元素
    int y = v1.at(0); // 访问v1的第一个元素，带边界检查
    ```

- **获取大小**：使用`size`函数获取`vector`中的元素个数。
    ```cpp
    size_t size = v1.size(); // 获取v1的大小
    ```

- **排序**：使用`sort`函数对`vector`中的元素进行排序。
    ```cpp
    sort(v4.begin(), v4.end()); // 对v4中的元素进行升序排序
    ```

- **查找元素**：使用`find`函数查找元素。
    ```cpp
    auto it = find(v4.begin(), v4.end(), 3); // 查找元素3
    if (it != v4.end()) {
        // 找到元素3
    }
    ```

### 示例代码

以下是一个简单的示例，展示了如何使用`vector`存储和操作数据：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<int> numbers = {5, 3, 8, 1, 2};

    // 添加元素
    numbers.push_back(6);

    // 访问元素
    cout << "First element: " << numbers[0] << endl;

    // 获取大小
    cout << "Size: " << numbers.size() << endl;

    // 排序
    sort(numbers.begin(), numbers.end());

    // 输出排序后的元素
    cout << "Sorted elements: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
```

在你的代码中，`vector<string> yesterday(n), today(m), new1(k);`声明了三个`vector`，分别用于存储昨天派遣潜艇的节点、所有相连节点已被发现的节点和新发现的节点。