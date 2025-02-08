'''
Some numbers have funny properties. For example:

89 --> 8¹ + 9² = 89 * 1
695 --> 6² + 9³ + 5⁴ = 1390 = 695 * 2
46288 --> 4³ + 6⁴ + 2⁵ + 8⁶ + 8⁷ = 2360688 = 46288 * 51

Given two positive integers n and p, we want to find a positive integer k, if it exists, such that the sum of the digits of n raised to consecutive powers starting from p is equal to k * n.

In other words, writing the consecutive digits of n as a, b, c, d ..., is there an integer k such that:

(a^p + b^(p+1) + c^(p+2) + d^(p+3) + ...) = n * k

If it is the case we will return k, if not return -1.

Note: n and p will always be strictly positive integers.

Examples:
n = 89; p = 1 ---> 1 since 8¹ + 9² = 89 = 89 * 1

n = 92; p = 1 ---> -1 since there is no k such that 9¹ + 2² equals 92 * k

n = 695; p = 2 ---> 2 since 6² + 9³ + 5⁴ = 1390 = 695 * 2

n = 46288; p = 3 ---> 51 since 4³ + 6⁴ + 2⁵ + 8⁶ + 8⁷ = 2360688 = 46288 * 51
'''
def dig_pow(n, p):
    s = sum(int(d) ** (p + i) for i, d in enumerate(str(n)))
    return s // n if s % n == 0 else -1
# 是 Python 内置函数，用于将一个可迭代对象（如列表、字符串等）组合为一个索引序列，同时列出数据和数据下标，
# 通常用在 for 循环中。它的语法如下：
# enumerate(iterable, start=0)
'''
str(n) 将数字 n 转换为字符串，以便逐位处理。
enumerate(str(n)) 将字符串 n 转换为一个枚举对象，每个元素是一个 (index, digit) 元组。
for i, d in enumerate(str(n)) 遍历枚举对象，i 是当前位的索引，d 是当前位的字符。
int(d) ** (p + i) 计算当前位的数字 d 的 (p + i) 次幂。
sum(...) 计算所有位的幂的和。
例如，对于 n = 695 和 p = 2：

str(n) 生成字符串 "695".
enumerate(str(n)) 生成枚举对象 [(0, '6'), (1, '9'), (2, '5')].
计算 6^2 + 9^3 + 5^4.
最终，函数返回 s // n 如果 s 可以被 n 整除，否则返回 -1。
'''

### Other Solutions
def dig_pow(n, p):
    sum_exp = sum( int(d) ** p for p, d in enumerate(str(n), p) )# enumerate(str(n), p) 从 p 开始枚举
    return sum_exp // n if sum_exp % n == 0 else -1

for i in enumerate("abc"):
    print(i)
    # (0, 'a')
    # (1, 'b')
    # (2, 'c')