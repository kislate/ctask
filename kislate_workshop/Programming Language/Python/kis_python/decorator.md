### 装饰器是什么

装饰器是 Python 中的一种高级特性，它允许你在不修改函数定义的情况下，向函数添加额外的功能。装饰器本质上是一个高阶函数，它接受一个函数作为参数，并返回一个新的函数。装饰器通常用于日志记录、性能计数、访问控制和记忆化等场景。

### 装饰器的基本语法

装饰器的基本语法使用 `@` 符号，放在函数定义的前一行。例如：

```python
@decorator_function
def some_function():
    
```

这相当于：

```python
def some_function():
    pass

some_function = decorator_function(some_function)
```

### 你的自定义装饰器分析

以下是你提供的自定义装饰器 `memoized` 的代码：

```python
def memoized(f):
    cache = {}
    def wrapped(k):
        if k not in cache:
            cache[k] = f(k)
        return cache[k]
    return wrapped

@memoized
def fibonacci(n):
    if n in [0, 1]:
        return n
    return fibonacci(n - 1) + fibonacci(n - 2)
```

### 详细解释

1. **定义装饰器 `memoized`**：
   ```python
   def memoized(f):
       cache = {}
   ```
   - `memoized` 是一个装饰器函数，它接受一个函数 `f` 作为参数。
   - `cache` 是一个字典，用于存储已经计算过的结果。

2. **定义内部函数 `wrapped`**：
   ```python
   def wrapped(k):
       if k not in cache:
           cache[k] = f(k)
       return cache[k]
   ```
   - `wrapped` 是一个内部函数，它接受一个参数 `k`。
   - 首先检查 `k` 是否在 `cache` 中。如果不在，则计算 `f(k)` 并将结果存储在 `cache` 中。
   - 最后返回缓存的结果。

3. **返回 `wrapped` 函数**：
   ```python
   return wrapped
   ```
   - `memoized` 装饰器返回 `wrapped` 函数，这个函数将替代原始的 `f` 函数。

4. **使用装饰器 `@memoized`**：
   ```python
   @memoized
   def fibonacci(n):
       if n in [0, 1]:
           return n
       return fibonacci(n - 1) + fibonacci(n - 2)
   ```
   - 使用 `@memoized` 装饰器装饰 `fibonacci` 函数。
   - 定义递归的 `fibonacci` 函数。如果 `n` 是 0 或 1，直接返回 `n`。否则，递归计算 `fibonacci(n - 1)` 和 `fibonacci(n - 2)` 的和。

### 测试

你可以使用以下代码来测试优化后的 Fibonacci 函数：

```python
print(fibonacci(10))  # 输出: 55
print(fibonacci(20))  # 输出: 6765
print(fibonacci(30))  # 输出: 832040
print(fibonacci(50))  # 输出: 12586269025
print(fibonacci(100)) # 输出: 354224848179261915075
```

### 总结

装饰器是 Python 中的一种高级特性，允许你在不修改函数定义的情况下，向函数添加额外的功能。你的自定义装饰器 `memoized` 使用了一个字典 `cache` 来存储已经计算过的结果，从而避免了重复计算，提高了递归 Fibonacci 函数的性能。
