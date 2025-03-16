'''
/*
图案重现（pattern）
【题目描述】
现在给你 n 个 8 ×8 的字符矩阵, 仅由大小写的 *、k、q、r、b、n、q 组成，你需
要判断第 i 个字符矩阵在之前出现过几次。
【输入格式】
输入共 8 ·n + 1 行。
输入的第一行包含一个正整数 n ，分别表示有 n 个字符矩阵。
接下来 8 ·n 行, 依次表示这 n 个字符矩阵。
【输出格式】
输出共 n 行，表示这个字符矩阵是第几次出现。
'''
def main(): #cos `C语言`
    n = int(input())
    pattern_dict = {}
    for i in range(n):
        pattern = []
        for j in range(8):
            pattern.append(input())
        pattern_dict[str(pattern)] = pattern_dict.get(str(pattern), 0) + 1
        print(int(pattern_dict[str(pattern)]))
if __name__ == '__main__':
    main()