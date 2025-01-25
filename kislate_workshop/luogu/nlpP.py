
n, m = map(int, input().split())#这就是一种获得两个整数的方法
#map() 的作用是将一个函数应用于一个或多个序列的每个元素，返回一个迭代器

str_dict = {}
for _ in range(n):
    key, value = input().split()
    str_dict[key] = value

for _ in range(m):
    sentence = input()
    output = []
    start = 0

    while start < len(sentence):
        p = sentence.find('{', start)
        if p == -1:
            # 没有找到，直接输出剩余部分
            output.append(sentence[start:])
            break

        output.append(sentence[start:p])
        q = sentence.find('}', p)
        if q == -1:
            output.append(sentence[p:])
            break

        key = sentence[p + 1:q]
        if key in str_dict:
            output.append(str_dict[key])
        else:
            output.append('{' + key + '}')

        start = q + 1

    print(''.join(output))

    #python的速通解法