# T586192 字符串分析

## 题目描述

1945 年，华小科作为一名宾夕法尼亚大学的研究生，她所在的团队正在开发全球首台电子数字计算机 ENIAC。在这个过程中，她的职责是进制转换。她需要将文档中一些十进制数字转换为十六进制。

团队提供了一个长长的字符串，其中一些数字需要进行进制转换，而另一些则不必。团队的其他成员已经对字符串进行了预处理，所有需要转换的数字都已经用大括号 `{}` 进行了标记，而没有被大括号包围的十进制数字则不需要转换。

例如，字符串 `qwer 1234 epr {12}`，只需要转换大括号中的 `12`，而前面的 `1234` 无需转换。

遗憾的是，由于技术限制，在大括号内，数字的左右还可能存在一些空格。转换数字后，需要去掉数字两侧的空格，只保留数字的值。输出的十六进制数字应以 `0x` 开头，**数值中的字母均应大写**。请你帮助华小科解决这个问题。

## 输入格式

输入一行一个字符串 $S$，代表需要处理的字符串。

## 输出格式

输出一行一个字符串，代表进制转换后的字符串。

## 输入输出样例 #1

### 输入 #1

```
Dad, today is my {12} year old birthday.
```

### 输出 #1

```
Dad, today is my 0xC year old birthday.
```

## 输入输出样例 #2

### 输入 #2

```
The number 11 is { 11 } in hex.
```

### 输出 #2

```
The number 11 is 0xB in hex.
```

## 说明/提示

对于所有测试数据，保证 $1 \le |S| \le 10^6$，字符串 $S$ 仅包含大小写英文字母、阿拉伯数字、`,`、`.`、`{`、`}` 和空格，大括号中的数字小于 $2^{31}$ 且为正数。

![](https://cdn.luogu.com.cn/upload/image_hosting/hl2sjnyc.png)

特殊性质 A：字符串中不包含 `{` 和 `}`。

特殊性质 B：大括号中不包含空格。

特殊性质 C：大括号中数字小于 $10$。

其中，$|S|$ 代表字符串 $S$ 的长度。

## 下面是代码实现(比赛版)
```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
    string string_raw;
    int num = 0;
    getline(cin, string_raw);
    bool flag_1 = false;
    bool flag_2 = true;
    bool flag_num = false;

    for (const auto &c : string_raw) {
        if (c == '{') {
            flag_1 = true;
            flag_2 = false;
            flag_num = false;
            num = 0;
            continue;
        }
        if (flag_1 && c >= '0' && c <= '9' && !flag_2) {
            flag_num = true;
            num = num * 10 + (c - '0');
            continue;
        }
        if (c == '}') {
            if (flag_num) { 
                printf("0x%X", num);
            }
            flag_2 = true;
            flag_1 = false;
            flag_num = false;
            num = 0; 
            continue;
        }
        if (flag_1 && flag_num && (c < '0' || c > '9')) {
            printf("0x%X", num);
            num = 0;
            flag_num = false;
            flag_1 = false;
            flag_2 = false;
            cout << c; 
            continue;
        }
        if (flag_2 && !flag_1 && !flag_num) {
            cout << c;
        }
    }
    return 0;
}
```

## 下面给一个大佬解法:
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    string s;
    getline(cin.s);
    stringstream sin(s).res;
    while(getline(sin,s,'{')
    {
        res << s;
        if(sin.peek()==EOF) break;
        getline(sin,s,'}');
        res << std::hex << std::uppercase "0x" << atoi(s.c_str());
    }
    cout << res.str() << endl;
}
```