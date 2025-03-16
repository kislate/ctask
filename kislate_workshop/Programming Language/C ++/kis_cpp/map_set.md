好的，下面我将详细解释 C++ 中 `unordered_map` 和 `unordered_set` 容器，包括它们的概念、特点、用法、示例以及一些最佳实践。

**核心概念**

`unordered_map` 和 `unordered_set` 是 C++ 标准模板库 (STL) 中提供的关联容器，它们都基于哈希表实现。这意味着它们提供了平均时间复杂度为 O(1) 的插入、删除和查找操作。  不过在最坏的情况下，时间复杂度可能退化为 O(n)，其中 n 是容器中元素的数量（这种情况通常发生在哈希冲突非常严重的时候）。

**1. `unordered_map`**

*   **定义:** `unordered_map` 是一种关联容器，用于存储键值对 (key-value pairs)。  每个键是唯一的，并且与一个值相关联。
*   **实现:** 基于哈希表，使用哈希函数将键映射到桶（bucket）中。
*   **头文件:** `#include <unordered_map>`
*   **模板参数:**
    *   `Key`: 键的类型。
    *   `T`: 值的类型。
    *   `Hash`: （可选）哈希函数对象，默认为 `std::hash<Key>`。
    *   `KeyEqual`: （可选）键的相等比较函数对象，默认为 `std::equal_to<Key>`。
*   **特点:**
    *   **快速查找:** 平均 O(1) 的查找复杂度。
    *   **无序:** 元素没有特定的顺序（不像 `std::map` 那样按键排序）。
    *   **键的唯一性:** 每个键只能出现一次。
    *   **允许 `nullptr` 作为键:** 在 C++11 之后，某些实现允许使用 `nullptr` 作为键（虽然不常见）。

**`unordered_map` 的常用方法:**

| 方法              | 描述                                                                                                                          |
| ----------------- | ---------------------------------------------------------------------------------------------------------------------------- |
| `unordered_map()` | 构造函数，创建空的 `unordered_map`。                                                                                       |
| `insert(pair)`   | 插入一个键值对。如果键已经存在，则不插入。                                                                                             |
| `erase(key)`      | 删除键为 `key` 的元素。返回删除的元素数量（通常为 0 或 1）。                                                                   |
| `find(key)`       | 查找键为 `key` 的元素。如果找到，返回指向该元素的迭代器；否则，返回 `end()`。                                                               |
| `count(key)`      | 返回键为 `key` 的元素数量（通常为 0 或 1）。                                                                                   |
| `size()`          | 返回 `unordered_map` 中元素的数量。                                                                                       |
| `empty()`         | 检查 `unordered_map` 是否为空。                                                                                             |
| `clear()`         | 清空 `unordered_map` 中的所有元素。                                                                                         |
| `begin()`         | 返回指向第一个元素的迭代器。                                                                                                |
| `end()`           | 返回指向最后一个元素之后位置的迭代器。                                                                                      |
| `operator[]`      | 访问键为 `key` 的元素。如果键不存在，则插入一个新的键值对，其中值是默认构造的值。                                                          |
| `at(key)`         | 访问键为 `key` 的元素。如果键不存在，则抛出 `std::out_of_range` 异常。                                                               |
| `bucket_count()`  | 返回桶的数量。                                                                                                              |
| `load_factor()`   | 返回当前负载因子（元素数量 / 桶数量）。                                                                                       |
| `max_load_factor()`| 获取或设置最大负载因子。当负载因子超过最大负载因子时，哈希表会自动重新哈希（rehash），增加桶的数量，以减少冲突。                                |
| `rehash(n)`       | 强制重新哈希，使得桶的数量至少为 `n`。这可以提高性能，但会消耗更多内存。                                                              |
| `reserve(n)`      | 预留空间，使得 `unordered_map` 至少可以容纳 `n` 个元素，而无需重新哈希。                                                                  |

**`unordered_map` 的示例:**

```cpp
#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    // 创建一个 unordered_map，键是字符串，值是整数
    std::unordered_map<std::string, int> ages;

    // 插入键值对
    ages["Alice"] = 30;
    ages["Bob"] = 25;
    ages.insert({"Charlie", 35}); // C++11 之后可以使用初始化列表

    // 访问元素
    std::cout << "Alice's age: " << ages["Alice"] << std::endl; // 输出: Alice's age: 30

    // 查找元素
    auto it = ages.find("Bob");
    if (it != ages.end()) {
        std::cout << "Bob's age: " << it->second << std::endl; // 输出: Bob's age: 25
    } else {
        std::cout << "Bob not found" << std::endl;
    }

    // 检查键是否存在
    if (ages.count("David") > 0) {
        std::cout << "David exists" << std::endl;
    } else {
        std::cout << "David does not exist" << std::endl; // 输出: David does not exist
    }

    // 遍历 unordered_map
    for (const auto& pair : ages) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    // 输出 (顺序不固定):
    // Charlie: 35
    // Alice: 30
    // Bob: 25

    // 删除元素
    ages.erase("Alice");

    // 检查 unordered_map 的大小
    std::cout << "Size: " << ages.size() << std::endl; // 输出: Size: 2

    return 0;
}
```

**2. `unordered_set`**

*   **定义:** `unordered_set` 是一种关联容器，用于存储唯一的元素。 它本质上是一个只存储键的 `unordered_map`。
*   **实现:** 基于哈希表。
*   **头文件:** `#include <unordered_set>`
*   **模板参数:**
    *   `Key`: 元素的类型。
    *   `Hash`: （可选）哈希函数对象，默认为 `std::hash<Key>`。
    *   `KeyEqual`: （可选）相等比较函数对象，默认为 `std::equal_to<Key>`。
*   **特点:**
    *   **快速查找:** 平均 O(1) 的查找复杂度。
    *   **无序:** 元素没有特定的顺序。
    *   **元素的唯一性:** 每个元素只能出现一次。

**`unordered_set` 的常用方法:**

| 方法              | 描述                                                                                                                          |
| ----------------- | ---------------------------------------------------------------------------------------------------------------------------- |
| `unordered_set()` | 构造函数，创建空的 `unordered_set`。                                                                                       |
| `insert(value)`  | 插入一个元素。如果元素已经存在，则不插入。                                                                                             |
| `erase(value)`     | 删除值为 `value` 的元素。返回删除的元素数量（通常为 0 或 1）。                                                                   |
| `find(value)`      | 查找值为 `value` 的元素。如果找到，返回指向该元素的迭代器；否则，返回 `end()`。                                                               |
| `count(value)`     | 返回值为 `value` 的元素数量（通常为 0 或 1）。                                                                                   |
| `size()`          | 返回 `unordered_set` 中元素的数量。                                                                                       |
| `empty()`         | 检查 `unordered_set` 是否为空。                                                                                             |
| `clear()`         | 清空 `unordered_set` 中的所有元素。                                                                                         |
| `begin()`         | 返回指向第一个元素的迭代器。                                                                                                |
| `end()`          | 返回指向最后一个元素之后位置的迭代器。                                                                                      |
| `bucket_count()`  | 返回桶的数量。                                                                                                              |
| `load_factor()`   | 返回当前负载因子（元素数量 / 桶数量）。                                                                                       |
| `max_load_factor()`| 获取或设置最大负载因子。当负载因子超过最大负载因子时，哈希表会自动重新哈希（rehash），增加桶的数量，以减少冲突。                                |
| `rehash(n)`       | 强制重新哈希，使得桶的数量至少为 `n`。这可以提高性能，但会消耗更多内存。                                                              |
| `reserve(n)`      | 预留空间，使得 `unordered_set` 至少可以容纳 `n` 个元素，而无需重新哈希。                                                                  |

**`unordered_set` 的示例:**

```cpp
#include <iostream>
#include <unordered_set>
#include <string>

int main() {
    // 创建一个 unordered_set，存储字符串
    std::unordered_set<std::string> names;

    // 插入元素
    names.insert("Alice");
    names.insert("Bob");
    names.insert("Charlie");
    names.insert("Alice"); // 重复插入，会被忽略

    // 查找元素
    if (names.find("Bob") != names.end()) {
        std::cout << "Bob is in the set" << std::endl; // 输出: Bob is in the set
    } else {
        std::cout << "Bob is not in the set" << std::endl;
    }

    // 检查元素是否存在
    if (names.count("David") > 0) {
        std::cout << "David is in the set" << std::endl;
    } else {
        std::cout << "David is not in the set" << std::endl; // 输出: David is not in the set
    }

    // 遍历 unordered_set
    for (const auto& name : names) {
        std::cout << name << std::endl;
    }
    // 输出 (顺序不固定):
    // Charlie
    // Alice
    // Bob

    // 删除元素
    names.erase("Alice");

    // 检查 unordered_set 的大小
    std::cout << "Size: " << names.size() << std::endl; // 输出: Size: 2

    return 0;
}
```

**自定义哈希函数和相等比较函数**

如果你的键类型是自定义的类或结构体，你需要提供自定义的哈希函数和相等比较函数，因为默认的 `std::hash` 和 `std::equal_to` 可能无法正确处理你的类型。

```cpp
#include <iostream>
#include <unordered_map>
#include <unordered_set>

struct Point {
    int x;
    int y;
};

// 自定义哈希函数
struct PointHash {
    size_t operator()(const Point& p) const {
        // 一个简单的哈希函数，可以将 x 和 y 组合成一个哈希值
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
    }
};

// 自定义相等比较函数
struct PointEqual {
    bool operator()(const Point& p1, const Point& p2) const {
        return p1.x == p2.x && p1.y == p2.y;
    }
};

int main() {
    // 使用自定义哈希函数和相等比较函数
    std::unordered_map<Point, int, PointHash, PointEqual> pointMap;

    Point p1 = {1, 2};
    Point p2 = {3, 4};
    Point p3 = {1, 2}; // 与 p1 相同

    pointMap[p1] = 10;
    pointMap[p2] = 20;

    std::cout << "p1 value: " << pointMap[p1] << std::endl; // 输出: p1 value: 10
    std::cout << "p3 value: " << pointMap[p3] << std::endl; // 输出: p3 value: 10 (因为 p3 与 p1 相同)

    // 使用自定义哈希函数和相等比较函数的 unordered_set
    std::unordered_set<Point, PointHash, PointEqual> pointSet;
    pointSet.insert(p1);
    pointSet.insert(p2);
    pointSet.insert(p3); // p3 不会被插入，因为它与 p1 相同

    std::cout << "pointSet size: " << pointSet.size() << std::endl; // 输出: pointSet size: 2

    return 0;
}
```

**选择 `unordered_map` 或 `unordered_set` 的时机**

*   **`unordered_map`:**  当你需要存储键值对，并且需要根据键快速查找对应的值时，使用 `unordered_map`。
*   **`unordered_set`:**  当你只需要存储唯一的元素，并且需要快速检查某个元素是否存在时，使用 `unordered_set`。

**性能考虑和最佳实践**

*   **哈希函数:** 选择一个好的哈希函数非常重要。 一个好的哈希函数应该尽可能地将键均匀地分布到桶中，以减少哈希冲突。 避免使用总是返回相同哈希值的哈希函数，因为这会导致所有元素都存储在同一个桶中，使得查找复杂度退化为 O(n)。
*   **负载因子:**  `unordered_map` 和 `unordered_set` 会自动重新哈希，以保持负载因子在一个合理的范围内。 你可以使用 `max_load_factor()` 来控制重新哈希的频率。
*   **预留空间:** 如果你知道 `unordered_map` 或 `unordered_set` 中将要存储的元素数量，可以使用 `reserve()` 来预留空间。 这样可以避免频繁的重新哈希，从而提高性能。
*   **自定义类型:**  对于自定义类型，务必提供合适的哈希函数和相等比较函数。

**总结**

`unordered_map` 和 `unordered_set` 是 C++ STL 中非常有用的关联容器，它们提供了快速的查找、插入和删除操作。 通过理解它们的特点、用法和性能考虑，你可以更好地利用它们来解决实际问题。  希望这个详细的解释能够帮助你更好地理解和使用 `unordered_map` 和 `unordered_set`。
