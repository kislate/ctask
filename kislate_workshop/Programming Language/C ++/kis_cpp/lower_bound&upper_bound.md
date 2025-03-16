`lower_bound` 和 `upper_bound` 是 C++ 标准库中的两个函数，通常用于在有序范围内查找元素。它们在 `<algorithm>` 头文件中定义，主要用于二分查找。

### `lower_bound`
`lower_bound` 函数用于在有序范围内查找第一个不小于给定值的元素的位置。

#### 函数原型
```cpp
template< class ForwardIt, class T >
ForwardIt lower_bound( ForwardIt first, ForwardIt last, const T& value );
```

#### 参数
- `first`：指向范围的起始位置。
- `last`：指向范围的结束位置。
- `value`：要查找的值。

#### 返回值
返回一个迭代器，指向第一个不小于 `value` 的元素。如果所有元素都小于 `value`，则返回 `last`。

#### 示例
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {1, 2, 4, 4, 5, 6, 8};
    auto it = std::lower_bound(v.begin(), v.end(), 4);
    if (it != v.end()) {
        std::cout << "The first element not less than 4 is " << *it << std::endl;
    } else {
        std::cout << "No element not less than 4 found" << std::endl;
    }
    return 0;
}
```

### `upper_bound`
`upper_bound` 函数用于在有序范围内查找第一个大于给定值的元素的位置。

#### 函数原型
```cpp
template< class ForwardIt, class T >
ForwardIt upper_bound( ForwardIt first, ForwardIt last, const T& value );
```

#### 参数
- `first`：指向范围的起始位置。
- `last`：指向范围的结束位置。
- `value`：要查找的值。

#### 返回值
返回一个迭代器，指向第一个大于 `value` 的元素。如果所有元素都小于或等于 `value`，则返回 `last`。

#### 示例
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {1, 2, 4, 4, 5, 6, 8};
    auto it = std::upper_bound(v.begin(), v.end(), 4);
    if (it != v.end()) {
        std::cout << "The first element greater than 4 is " << *it << std::endl;
    } else {
        std::cout << "No element greater than 4 found" << std::endl;
    }
    return 0;
}
```

### `lower_bound` 和 `upper_bound` 的区别
- `lower_bound` 返回第一个不小于给定值的元素的位置。
- `upper_bound` 返回第一个大于给定值的元素的位置。

### 示例代码
以下是一个完整的示例代码，展示了如何使用 `lower_bound` 和 `upper_bound`：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {1, 2, 4, 4, 5, 6, 8};

    // 使用 lower_bound 查找第一个不小于 4 的元素
    auto lower = std::lower_bound(v.begin(), v.end(), 4);
    if (lower != v.end()) {
        std::cout << "The first element not less than 4 is " << *lower << std::endl;
    } else {
        std::cout << "No element not less than 4 found" << std::endl;
    }

    // 使用 upper_bound 查找第一个大于 4 的元素
    auto upper = std::upper_bound(v.begin(), v.end(), 4);
    if (upper != v.end()) {
        std::cout << "The first element greater than 4 is " << *upper << std::endl;
    } else {
        std::cout << "No element greater than 4 found" << std::endl;
    }

    return 0;
}
```

### 总结
- `lower_bound` 和 `upper_bound` 是用于在有序范围内查找元素的函数。
- `lower_bound` 返回第一个不小于给定值的元素的位置。
- `upper_bound` 返回第一个大于给定值的元素的位置。
- 它们都使用二分查找算法，时间复杂度为 O(log n)。