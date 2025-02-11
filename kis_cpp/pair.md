在 C++ 中，`pair` 是一个模板类，用于存储一对值。它在 `<utility>` 头文件中定义。`pair` 可以存储两个不同类型的值，并且可以通过 `first` 和 `second` 成员变量来访问这两个值。

在你的代码中，`vector<pair<int, double>> operations(n);` 定义了一个大小为 `n` 的 `vector`，其中每个元素都是一个 `pair`，这个 `pair` 的第一个值是 `int` 类型，第二个值是 `double` 类型。

以下是一个简单的示例，展示了如何使用 `pair`：

```cpp
#include <iostream>
#include <utility> // 包含 pair 的定义
#include <vector>

using namespace std;

int main() {
    // 定义一个 pair，存储一个 int 和一个 double
    pair<int, double> p1;
    p1.first = 1;
    p1.second = 3.14;

    // 也可以使用 make_pair 函数来创建 pair
    pair<int, double> p2 = make_pair(2, 2.71);

    // 输出 pair 的值
    cout << "p1: (" << p1.first << ", " << p1.second << ")" << endl;
    cout << "p2: (" << p2.first << ", " << p2.second << ")" << endl;

    // 定义一个 vector，存储多个 pair
    vector<pair<int, double>> operations;
    operations.push_back(p1);
    operations.push_back(p2);

    // 输出 vector 中的 pair 的值
    for (const auto& op : operations) {
        cout << "(" << op.first << ", " << op.second << ")" << endl;
    }

    return 0;
}
```

在这个示例中，我们定义了两个 `pair`，并将它们存储在一个 `vector` 中。然后，我们遍历 `vector` 并输出每个 `pair` 的值。

在你的代码中，`operations` 向量将存储所有的坐标变换操作，每个操作由一个整数（表示操作类型）和一个双精度浮点数（表示拉伸系数或旋转角度）组成。