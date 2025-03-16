# `unordered_set` 和 `unordered_map` 详解

## 1. `unordered_set`

### 特点
- 存储**唯一元素**，不允许重复。
- 基于哈希表实现，查找、插入、删除的平均时间复杂度为 **O(1)**。
- 元素无序存储。

### 常用操作
```cpp
#include <unordered_set>
#include <iostream>

int main() {
    std::unordered_set<int> s = {1, 2, 3};

    // 插入元素
    s.insert(4);

    // 查找元素
    if (s.find(3) != s.end()) {
        // 元素存在
    }

    // 删除元素
    s.erase(2);

    // 计数元素
    if (s.count(1) > 0) {
        // 元素存在
    }

    // 遍历
    for (const auto& elem : s) {
        std::cout << elem << " ";
    }
}
```

### 适用场景
- 需要快速判断元素是否存在。
- 需要存储唯一元素且不关心顺序。

---

## 2. `unordered_map`

### 特点
- 存储**键值对**，键唯一，值可重复。
- 基于哈希表实现，查找、插入、删除的平均时间复杂度为 **O(1)**。
- 键值对无序存储。

### 常用操作
```cpp
#include <unordered_map>
#include <iostream>

int main() {
    std::unordered_map<std::string, int> m = {{"Alice", 25}, {"Bob", 30}};

    // 插入键值对
    m["Charlie"] = 35;

    // 查找键
    if (m.find("Bob") != m.end()) {
        int age = m["Bob"];
    }

    // 删除键值对
    m.erase("Alice");

    // 计数键
    if (m.count("Alice") > 0) {
        // 键存在
    }

    // 遍历
    for (const auto& [key, value] : m) {
        std::cout << key << ": " << value << "\n";
    }
}
```

### 适用场景
- 需要快速通过键查找值。
- 需要存储键值对且不关心顺序。

---

## 3. 对比表格

| 特性                | `unordered_set`                  | `unordered_map`                  |
|---------------------|----------------------------------|----------------------------------|
| **存储内容**        | 唯一元素                         | 键值对（键唯一）                |
| **查找方式**        | 直接查找元素                     | 通过键查找值                    |
| **插入方式**        | `insert(element)`                | `insert({key, value})` 或 `[]`   |
| **时间复杂度**      | 平均 O(1)，最坏 O(n)             | 平均 O(1)，最坏 O(n)            |
| **内存占用**        | 较低                             | 较高（需存储键值对）            |

---

## 4. 性能优化

### 自定义哈希函数
```cpp
#include <unordered_set>
#include <string>

struct Person {
    std::string name;
    int age;

    // 必须定义相等运算符
    bool operator==(const Person& other) const {
        return name == other.name && age == other.age;
    }
};

// 自定义哈希函数
struct PersonHash {
    size_t operator()(const Person& p) const {
        return std::hash<std::string>()(p.name) ^ std::hash<int>()(p.age);
    }
};

int main() {
    std::unordered_set<Person, PersonHash> s;
    s.insert({"Alice", 25});
}
```

### 预分配空间
```cpp
std::unordered_set<int> s;
s.reserve(1000);  // 预分配空间减少扩容次数
```

---

## 5. 注意事项

1. **哈希冲突**：
   - 哈希函数质量直接影响性能。
   - 最坏情况下时间复杂度退化为 O(n)。

2. **无序性**：
   - 迭代顺序不可预测，若需要有序请用 `set`/`map`。

3. **内存管理**：
   - 哈希表内存占用较高，尤其在存储大量数据时。

---

## 6. 总结

| 选择依据            | `unordered_set`                  | `unordered_map`                  |
|---------------------|----------------------------------|----------------------------------|
| **是否需要键值对**  | ❌ 否                            | ✅ 是                            |
| **是否需要有序**    | ❌ 否                            | ❌ 否                            |
| **内存敏感度**      | ✅ 低内存占用                    | ❌ 高内存占用                    |