'''
How can you tell an extrovert from an introvert at NSA?
Va gur ryringbef, gur rkgebireg ybbxf ng gur BGURE thl'f fubrf.

I found this joke on USENET, but the punchline is scrambled. Maybe you can decipher it?
According to Wikipedia, ROT13 is frequently used to obfuscate jokes on USENET.

For this task you're only supposed to substitute characters. Not spaces, punctuation, numbers, etc.

Test examples:

"EBG13 rknzcyr." -> "ROT13 example."

"This is my first ROT13 excercise!" -> "Guvf vf zl svefg EBG13 rkprepvfr!
'''
def rot13(message):
    #your code here
    return "".join([chr(ord(i) + 13) if ord(i) + 13 <= 90 or ord(i) + 13 <= 122 else chr(ord(i) - 13) for i in message])
# 没成功
# ord() 函数是 chr() 函数（对于8位的ASCII字符串）或 unichr() 函数（对于Unicode对象）的配对函数，

def rot13(message):
    str = []
    for i in message:
        if i.isalpha():
            if i.islower():
                temp = (ord(i) + 13 - ord("a"))%26 + ord("a")
                str.append(chr(temp))
            else:
                temp = (ord(i) + 13 - ord("A"))%26 + ord("A")
                str.append(chr(temp))
        else:
            str.append(i)
    return "".join(str)


def rot13(message):
    def decode(c):
        if 'a' <= c <= 'z':
            base = 'a'
        elif 'A' <= c <= 'Z':
            base = 'A'
        else:
            return c
        return chr((ord(c) - ord(base) + 13) % 26 + ord(base))
    return "".join(decode(c) for c in message)
# 这个方法在内部定义了一个函数

import string

def rot13(message):
    first = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'
    trance = 'NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm'
    return message.translate(str.maketrans(first, trance))
# str是一个类,maketrans必须通过str类调用

def rot13(message):
    import codecs
    return codecs.encode(message, 'rot_13')# md 无赖解法
# codecs模块是python的一个编解码器注册和基类，它提供了一个编解码器基类和一些常见编解码器的注册，比如base64、bz2、hex、rot_13等等

def rot13(message):
    PAIRS = dict(zip("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
        "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM"))
    ### zip() 函数用于将可迭代的对象作为参数，将对象中对应的元素打包成一个个元组，然后返回由这些元组组成的列表。
    ## 如果打包的个数多了，那么多出来的元素会被忽略
    #  dict() 将元组转换为字典
    return "".join(PAIRS.get(c, c) for c in message)
# dict.get(key, default=None) 返回指定键的值，如果值不在字典中返回默认值
# 这里的默认值就是c