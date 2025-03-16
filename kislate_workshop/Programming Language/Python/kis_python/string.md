# `string` 模块

`string` 模块提供了一些常量和函数，用于处理字符串操作。

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

## `str.maketrans` 和 `str.translate`

`str.maketrans` 方法用于创建一个字符映射表，用于字符替换。它可以接受两个参数（两个等长的字符串），或者一个字典。

```python
str.maketrans(x, y)
```

示例：

```python
table = str.maketrans('abc', '123')
print(table)  # 输出: {97: 49, 98: 50, 99: 51}
```

`str.translate` 方法用于根据给定的映射表（由 `str.maketrans` 创建）替换字符串中的字符。

```python
str.translate(table)
```

示例：

```python
table = str.maketrans('abc', '123')
result = 'abc'.translate(table)
print(result)  # 输出: '123'
```

结合使用 `str.maketrans` 和 `str.translate` 可以实现字符的批量替换或翻译。例如，在你的 `rot13` 函数中：

```python
def rot13(message):
    first = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'
    trance = 'NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm'
    return message.translate(str.maketrans(first, trance))

# 测试
print(rot13("Hello World!"))  # 输出: Uryyb Jbeyq!
print(rot13("Uryyb Jbeyq!"))  # 输出: Hello World!
```

在这个实现中：
1. `str.maketrans(first, trance)` 创建了一个字符映射表，将 `first` 中的每个字符映射到 `trance` 中的对应字符。
2. `message.translate(str.maketrans(first, trance))` 使用这个映射表对 `message` 进行字符替换，实现 ROT13 加密/解密。

`str.translate()` 方法可以接受一个字典作为参数，用于字符替换。这个字典的键是要替换的字符的 Unicode 码点，值是替换后的字符的 Unicode 码点。

示例：

```python
def custom_translate(message):
    translation_table = {ord('a'): ord('1'), ord('b'): ord('2'), ord('c'): ord('3')}
    return message.translate(translation_table)

# 测试
print(custom_translate("abc"))  # 输出: '123'
print(custom_translate("hello abc world"))  # 输出: 'hello 123 world'
```

使用字典实现 ROT13：

```python
def rot13(message):
    translation_table = {ord(c): ord('A') + (ord(c) - ord('A') + 13) % 26 for c in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'}
    translation_table.update({ord(c): ord('a') + (ord(c) - ord('a') + 13) % 26 for c in 'abcdefghijklmnopqrstuvwxyz'})
    return message.translate(translation_table)

# 测试
print(rot13("Hello World!"))  # 输出: Uryyb Jbeyq!
print(rot13("Uryyb Jbeyq!"))  # 输出: Hello World!
```

总结：
- `str.translate()` 方法可以接受一个字典作为参数，用于字符替换。
- 字典的键是要替换的字符的 Unicode 码点，值是替换后的字符的 Unicode 码点。
