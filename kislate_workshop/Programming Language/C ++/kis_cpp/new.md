# C++ 中的 `new` 运算符

## 作用
- **动态内存分配**：在堆（heap）上分配内存，返回指向该内存的指针。
- **手动管理**：必须显式使用 `delete` 释放内存，否则会导致内存泄漏。

---

## 基本用法

### 1. 分配单个对象
```cpp
int* p = new int;  // 分配一个 int 类型的内存
*p = 10;           // 赋值
delete p;          // 释放内存
```

### 2. 分配数组
```cpp
int* arr = new int[5];  // 分配一个包含 5 个 int 的数组
delete[] arr;           // 释放数组内存（注意 `[]`）
```

### 3. 初始化对象
```cpp
int* p = new int(42);  // 分配内存并初始化为 42
```

---

## 注意事项

### 1. 内存泄漏
- 忘记 `delete` 会导致内存泄漏：
    ```cpp
    int* p = new int;
    // 忘记 delete p; → 内存泄漏！
    ```

### 2. 野指针
- 释放内存后，指针仍指向原地址：
    ```cpp
    delete p;
    *p = 10;  // 错误：p 是野指针
    ```

### 3. 异常处理
- 使用 `nothrow` 避免内存分配失败时抛出异常：
    ```cpp
    int* p = new (std::nothrow) int;
    if (!p) {
            std::cout << "内存分配失败！";
    }
    ```

---

## `new` vs `malloc`

| 特性               | `new`                          | `malloc`                  |
|--------------------|--------------------------------|---------------------------|
| **语言**           | C++ 运算符                     | C 函数                    |
| **构造函数调用**   | 会调用构造函数                 | 不会调用                  |
| **返回类型**       | 类型安全的指针（如 `int*`）    | `void*`（需强制类型转换） |
| **失败行为**       | 抛出 `std::bad_alloc` 异常     | 返回 `NULL`               |

---

## 示例代码
```cpp
#include <iostream>

int main() {
        // 分配单个对象
        int* p = new int(42);
        std::cout << "Value: " << *p << std::endl;
        delete p;

        // 分配数组
        int* arr = new int[5];
        for (int i = 0; i < 5; ++i) {
                arr[i] = i + 1;
        }
        for (int i = 0; i < 5; ++i) {
                std::cout << arr[i] << " ";
        }
        delete[] arr;

        return 0;
}
```

---

## 总结
- 使用 `new` 后必须配对使用 `delete` 或 `delete[]`。
- 推荐优先使用智能指针（如 `std::unique_ptr`、`std::shared_ptr`）自动管理内存。
- 避免野指针：释放后置空指针（`p = nullptr;`）。