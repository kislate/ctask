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

以下是一个使用 `string` 模块常量和函数的示例：

```python
import string

# 使用 string.ascii_lowercase
lowercase_letters = string.ascii_lowercase
print(lowercase_letters)  # 输出: 'abcdefghijklmnopqrstuvwxyz'

# 使用 string.digits
digits = string.digits
print(digits)  # 输出: '0123456789'

# 使用 string.capwords
s = "hello world"
capitalized = string.capwords(s)
print(capitalized)  # 输出: "Hello World"
```

这些常量和函数在处理字符串操作时非常有用，可以简化代码并提高可读性。


`map` 函数是 Python 的一个内置函数，用于将一个函数应用到一个或多个可迭代对象（如列表、元组等）的每个元素，并返回一个迭代器。`map` 函数的语法如下：

```python
map(function, iterable, ...)
```

- `function` 是一个函数，它将应用到 `iterable` 的每个元素。
- `iterable` 是一个或多个可迭代对象。

`map` 函数返回一个迭代器，其中包含应用函数后的结果。

以下是一些示例：

1. 将一个函数应用到一个列表的每个元素：

```python
def square(x):
    return x * x

numbers = [1, 2, 3, 4, 5]
squared_numbers = map(square, numbers)

print(list(squared_numbers))  # 输出 [1, 4, 9, 16, 25]
```

2. 使用 `lambda` 表达式：

```python
numbers = [1, 2, 3, 4, 5]
squared_numbers = map(lambda x: x * x, numbers)

print(list(squared_numbers))  # 输出 [1, 4, 9, 16, 25]
```

3. 将多个可迭代对象的元素作为参数传递给函数：

```python
numbers1 = [1, 2, 3]
numbers2 = [4, 5, 6]
summed_numbers = map(lambda x, y: x + y, numbers1, numbers2)

print(list(summed_numbers))  # 输出 [5, 7, 9]
```

在你的代码中，`map(int, str(n))` 用于将整数 

n

 的每一位转换为整数：

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

在这个函数中，`map(int, str(n))` 将字符串 

str(n)

 中的每个字符转换为整数，并使用 

enumerate

 来生成每一位的索引和对应的整数值。然后，计算每一位的幂的和，并检查是否可以被 n整除。


 enumerate

 是 Python 内置函数，用于将一个可迭代对象（如列表、字符串等）组合为一个索引序列，同时列出数据和数据下标，通常用在 `for` 循环中。它的语法如下：

```python
enumerate(iterable, start=0)
```

- `iterable` 是一个可迭代对象。
- `start` 是索引的起始位置，默认为 0。

在你的代码中，

enumerate

 用于遍历数字 

n

 的每一位，同时提供每一位的索引：

```python
def dig_pow(n, p):
    s = sum(int(d) ** (p + i) for i, d in enumerate(str(n)))
    return s // n if s % n == 0 else -1
```

具体解释如下：
1. 

str(n)

 将数字 

n

 转换为字符串，以便逐位处理。
2. 

enumerate(str(n))

 将字符串 

n

 转换为一个枚举对象，每个元素是一个 `(index, digit)` 元组。
3. 

for i, d in enumerate(str(n))

 遍历枚举对象，

i

 是当前位的索引，

d

 是当前位的字符。
4. 

int(d) ** (p + i)

 计算当前位的数字 

d

 的 `(p + i)` 次幂。
5. 

sum(...)

 计算所有位的幂的和。

例如，对于 

n = 695

 和 

p = 2

：
- 

str(n)

 生成字符串 `"695"`.
- 

enumerate(str(n))

 生成枚举对象 `[(0, '6'), (1, '9'), (2, '5')]`.
- 计算 `6^2 + 9^3 + 5^4`.

最终，函数返回 

s // n

 如果 

s

 可以被 

n

 整除，否则返回 `-1`。