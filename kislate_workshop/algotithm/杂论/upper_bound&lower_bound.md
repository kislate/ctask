
# C++ STL 二分查找函数详解

## 1. `lower_bound` 函数
### 定义
在有序区间 `[first, last)` 中查找第一个 **不小于** 指定值的元素位置。

**标准形式**：
```latex
template <class ForwardIt, class T>
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value)
```

### 参数说明
- $\texttt{first}$, $\texttt{last}$: 前向迭代器定义的范围
- $\texttt{value}$: 待查找的目标值
- $\texttt{comp}$ (可选): 自定义比较函数，形式为 $\texttt{bool comp(const T \&a, const T \&b)}$

### 数学表达
对于升序序列：
$$\exists\ x \in [first, last),\ \text{使得}\ x \geq \texttt{value}\ \text{且}\ \forall y \in [first, x),\ y < \texttt{value}$$

对于降序序列（需指定 `greater<T>()`）：
$$\exists\ x \in [first, last),\ \text{使得}\ x \leq \texttt{value}\ \text{且}\ \forall y \in [first, x),\ y > \texttt{value}$$ 

### 示例代码
```cpp
vector<int> v = {1, 3, 5, 7, 9};
auto it = lower_bound(v.begin(), v.end(), 4); 
// 返回指向5的迭代器（第一个≥4的元素）
```

---

## 2. `upper_bound` 函数
### 定义
在有序区间 `[first, last)` 中查找第一个 **大于** 指定值的元素位置。

**标准形式**：
```latex
template <class ForwardIt, class T>
ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& value)
```

### 参数说明
参数同 `lower_bound`，但查找条件不同。

### 数学表达
对于升序序列：
$$\exists\ x \in [first, last),\ \text{使得}\ x > \texttt{value}\ \text{且}\ \forall y \in [first, x),\ y \leq \texttt{value}$$

对于降序序列（需指定 `greater<T>()`）：
$$\exists\ x \in [first, last),\ \text{使得}\ x < \texttt{value}\ \text{且}\ \forall y \in [first, x),\ y \geq \texttt{value}$$ 

### 示例代码
```cpp
vector<int> v = {1, 3, 3, 5, 7};
auto it = upper_bound(v.begin(), v.end(), 3);
// 返回指向5的迭代器（第一个>3的元素）
```

---

## 对比表格
| 特性                | `lower_bound`           | `upper_bound`           |
|---------------------|-------------------------|-------------------------|
| **默认比较条件**     | $\geq$                  | $>$                     |
| **降序比较条件**     | $\leq$ (需 `greater<T>`) | $<$ (需 `greater<T>`)  |
| **时间复杂度**       | $O(\log n)$             | $O(\log n)$            |
| **返回值意义**       | 插入不破坏顺序的首位置  | 插入不破坏顺序的末位置  

---

## 应用场景
1. **范围查询**：配合使用可获取值域区间
   ```cpp
   auto [low, high] = equal_range(v.begin(), v.end(), target);
   ```
2. **维护有序序列**：用于插入新元素保持有序性
3. **离散数学应用**：计算序列中特定值的出现次数
   $$\texttt{upper\_bound - lower\_bound} = \text{出现次数}$$ 

---

> 提示：所有示例代码需要包含 `<algorithm>` 头文件，且序列必须预先排序。当使用自定义比较规则时，需要保证比较逻辑与排序规则一致。

- `P1020 导弹拦截`
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string line;
    getline(cin, line);
    istringstream iss(line);
    int height;
    vector<int> heights;
    while (iss >> height) heights.push_back(height);
    int n = heights.size();

    // 计算最长不上升子序列（Non-Increasing）
    vector<int> tail1;
    for (int num : heights) {
        auto it = upper_bound(tail1.begin(), tail1.end(), num, greater<int>());
        if (it == tail1.end()) {
            tail1.push_back(num);
        } else {
            *it = num;
        }
    }
    int ans1 = tail1.size();

    // 计算最长上升子序列（Increasing）
    vector<int> tail2;
    for (int num : heights) {
        auto it = lower_bound(tail2.begin(), tail2.end(), num);
        if (it == tail2.end()) {
            tail2.push_back(num);
        } else {
            *it = num;
        }
    }
    int ans2 = tail2.size();

    cout << ans1 << endl;
    cout << ans2 << endl;

    return 0;
}
```

注：以上内容综合了标准定义、数学表达和实际应用，结合了网页1-8的关键信息。如需完整代码示例，可参考[CSDN博客](https://blog.csdn.net/qq_40160605/article/details/80150252)。