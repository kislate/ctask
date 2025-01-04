'''
Jaden Casing Strings
295148886% of 20,97896,250 of 245,824jacobb16 Issues Reported
 Python
3.11
VIM
EMACS
Instructions
Output
Jaden Smith, the son of Will Smith, is the star of films such as The Karate Kid (2010) and After Earth (2013). Jaden is also known for some of his philosophy that he delivers via Twitter. When writing on Twitter, he is known for almost always capitalizing every word. For simplicity, you'll have to capitalize each word, check out how contractions are expected to be in the example below.

Your task is to convert strings to how they would be written by Jaden Smith. The strings are actual quotes from Jaden Smith, but they are not capitalized in the same way he originally typed them.

Example:

Not Jaden-Cased: "How can mirrors be real if our eyes aren't real"
Jaden-Cased:     "How Can Mirrors Be Real If Our Eyes Aren't Real"
Link to Jaden's former Twitter account @officialjaden via archive.org
'''
def to_jaden_case(string):
    # ...
    return ' '.join([i.capitalize() for i in string.split()])

# capitalize() 方法返回字符串的第一个字符的大写字母版本。


### 
def to_jaden_case(string):
    return ' '.join([i[0].upper() + i[1:].lower() if i else '' for i in string.split()])
# 通过切片的方式，将每个单词的首字母大写，其他字母小写

# 返回一堆i，在i 不是空字符串的情况下，如果是空字符串，那么就直接返回空字符串
# 把这个判断删掉后的代码如下
def to_jaden_case(string):
    return ' '.join([i[0].upper() + i[1:].lower() for i in string.split()])
## 一般情况下，我们不会对空字符串进行处理，因为这样会增加代码的复杂度，而且没有必要