'''
The rgb function is incomplete. Complete it so that passing in RGB decimal 
values will result in a hexadecimal representation being returned. Valid decimal values for RGB are 0 - 255. Any values that fall out of that range must be rounded to the closest valid value.

Note: Your answer should always be 6 characters long, the shorthand with 3 will not work here.

Examples (input --> output):
255, 255, 255 --> "FFFFFF"
255, 255, 300 --> "FFFFFF"
0, 0, 0       --> "000000"
148, 0, 211   --> "9400D3"
Algorithms
'''
def rgb(r, g, b):
    # your code here :)
    return ''.join([format(i, '02X') if 0 <= i <= 255 else 'FF' if i > 255 else'00' for i in [r,g,b]])


def rgb(r, g, b):
    round = lambda x: min(255, max(x, 0))
    return ("{:02X}" * 3).format(round(r), round(g), round(b))


format(value, format_spec)  # value 是要格式化的值，format_spec 是格式说明符

# 十进制整数
print(format(255, 'd'))  # 输出: 255

# 十六进制整数
print(format(255, 'x'))  # 输出: ff
print(format(255, 'X'))  # 输出: FF

# 浮点数
print(format(3.14159, '.2f'))  # 输出: 3.14

# 科学计数法
print(format(3.14159, '.2e'))  # 输出: 3.14e+00
print(format(3.14159, '.2E'))  # 输出: 3.14E+00

# 宽度为 2，不足两位时在前面补 0
print(format(5, '02'))  # 输出: 05



'''
常见的格式说明符
d：十进制整数。
x 或 X：十六进制整数（x 表示小写，X 表示大写）。
f：浮点数。
e 或 E：科学计数法表示的浮点数（e 表示小写，E 表示大写）。
02：表示宽度为 2，不足两位时在前面补 0。
示例
'''