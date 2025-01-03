# `string` 模块

`string` 模块提供了一些有用的常量和函数，用于处理字符串操作。以下是 `string` 模块中的一些常量和函数：

## 常量

1. **`string.ascii_letters`**：包含所有 ASCII 字母（大写和小写）。
    ```python
    'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
    ```

2. **`string.ascii_lowercase`**：包含所有小写 ASCII 字母。
    ```python
    'abcdefghijklmnopqrstuvwxyz'
    ```

3. **`string.ascii_uppercase`**：包含所有大写 ASCII 字母。
    ```python
    'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    ```

4. **`string.digits`**：包含所有数字字符。
    ```python
    '0123456789'
    ```

5. **`string.hexdigits`**：包含所有十六进制字符。
    ```python
    '0123456789abcdefABCDEF'
    ```

6. **`string.octdigits`**：包含所有八进制字符。
    ```python
    '01234567'
    ```

7. **`string.punctuation`**：包含所有标点符号字符。
    ```python
    '!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~'
    ```

8. **`string.printable`**：包含所有可打印字符，包括字母、数字、标点符号和空白字符。
    ```python
    '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~ \t\n\r\x0b\x0c'
    ```

9. **`string.whitespace`**：包含所有空白字符。
    ```python
    ' \t\n\r\x0b\x0c'
    ```

## 函数

1. **`string.capwords(s, sep=None)`**：将字符串 `s` 中的每个单词的首字母大写，并将其余字母小写。单词由 `sep` 分隔，默认为空格。
    ```python
    import string
    s = "hello world"
    print(string.capwords(s))  # 输出: "Hello World"
    ```

## 示例

```python
import string

# 使用 string.ascii_lowercase
print(string.ascii_lowercase)  # 输出: 'abcdefghijklmnopqrstuvwxyz'

# 使用 string.digits
print(string.digits)  # 输出: '0123456789'

# 使用 string.capwords
s = "hello world"
print(string.capwords(s))  # 输出: "Hello World"
```

## `map` 函数

`map` 函数将一个函数应用到一个或多个可迭代对象的每个元素，并返回一个迭代器。

```python
map(function, iterable, ...)
```

示例：

1. 将一个函数应用到一个列表的每个元素：
    ```python
    def square(x):
        return x * x

    numbers = [1, 2, 3, 4, 5]
    print(list(map(square, numbers)))  # 输出 [1, 4, 9, 16, 25]
    ```

2. 使用 `lambda` 表达式：
    ```python
    numbers = [1, 2, 3, 4, 5]
    print(list(map(lambda x: x * x, numbers)))  # 输出 [1, 4, 9, 16, 25]
    ```

3. 将多个可迭代对象的元素作为参数传递给函数：
    ```python
    numbers1 = [1, 2, 3]
    numbers2 = [4, 5, 6]
    print(list(map(lambda x, y: x + y, numbers1, numbers2)))  # 输出 [5, 7, 9]
    ```

## 示例代码

```python
def dig_pow(n, p):
    s = sum(d ** (p + i) for i, d in enumerate(map(int, str(n))))
    return s // n if s % n == 0 else -1

# 示例用法
print(dig_pow(89, 1))    # 输出 1
print(dig_pow(92, 1))    # 输出 -1
print(dig_pow(695, 2))   # 输出 2
print(dig_pow(46288, 3)) # 输出 51
```

`enumerate` 用于将一个可迭代对象组合为一个索引序列，通常用在 `for` 循环中。

```python
enumerate(iterable, start=0)
```

示例：

```python
def dig_pow(n, p):
    s = sum(int(d) ** (p + i) for i, d in enumerate(str(n)))
    return s // n if s % n == 0 else -1
```

解释：
1. `str(n)` 将数字 `n` 转换为字符串。
2. `enumerate(str(n))` 生成枚举对象。
3. `for i, d in enumerate(str(n))` 遍历枚举对象。
4. `int(d) ** (p + i)` 计算当前位的数字的 `(p + i)` 次幂。
5. `sum(...)` 计算所有位的幂的和。
