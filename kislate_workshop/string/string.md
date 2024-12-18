# C 字符串处理研讨会

## 目录
- [C 字符串处理研讨会](#c-字符串处理研讨会)
  - [目录](#目录)
  - [介绍](#介绍)
  - [字符串字面量和数组](#字符串字面量和数组)
  - [输入和输出函数](#输入和输出函数)
  - [字符串操作函数](#字符串操作函数)
  - [字符串比较函数](#字符串比较函数)
  - [字符串复制函数](#字符串复制函数)
  - [格式化输出](#格式化输出)
  - [其他字符串函数](#其他字符串函数)
  - [结论](#结论)

## 介绍
本文档涵盖了 C 语言中字符串处理的各个方面，包括字符串字面量、数组、输入/输出函数和常见的字符串操作函数。

## 字符串字面量和数组
```c
#include <stdio.h>
#define STLEN 14

int main(void) {
    char *p1 = "Klingon";
    p1[1] = 'F'; // 不能直接修改，因为 "Klingon" 是指向静态存储字符串的指针。
    char *p2 = "Klingon"; // p1 和 p2 指向相同的静态存储。
    char str1[] = "Klingon";
    char str2[] = "Klingon"; // str1 和 str2 是独立的副本。
    printf("Klingon");
    printf(": Beware the %ss", "Klingon");
}
```

## 输入和输出函数
```c
char words[STLEN];
puts("请输入一个字符串。");
fgets(words, STLEN, stdin); // 如果输入长度 <= STLEN，fgets 会存储 '\n'
puts(words); // 打印字符串，包括换行符
fputs(words, stdout); // fputs 不会添加换行符
printf("%s", words);
puts("输入字符串（空行退出）：");

while (fgets(words, 10, stdin) != NULL && words[0] != '\0') {
    fputs(words, stdout);
}
puts("完成");
```

## 字符串操作函数
```c
int i = 0;
while (words[i] != '\n') {
    i++;
}
words[i] = '\0'; // 移除换行符

while (getchar() != '\n') {
    continue;
}

while (fgets(words, 10, stdin) != NULL && words[0] != '\0') {
    i = 0;
    while (words[i] != '\n' && words[i] != '\0') {
        i++;
    }
    if (words[i] == '\n') {
        words[i] = '\0';
    } else {
        while (getchar() != '\n') {
            continue;
        }
    }
    puts(words);
}
puts("完成");
fputc('c', stdout);
```

## 字符串比较函数
```c
strcmp("kislate", "kislate"); // 如果相等返回 0
stricmp("kislate", "KISLATE"); // 不区分大小写的比较
strncmp("kislate", "kislate", 3); // 比较前 3 个字符
```

## 字符串复制函数
```c
strcpy(flower, "Rose");
const char *orig = "beast";
char copy[40] = "Be the best that you can be.";
char *ps;

puts(orig);
ps = strcpy(copy + 7, orig); // 从位置 7 开始将 "beast" 复制到 "copy"
puts(copy);
puts(ps);

strncpy(copy, "The worst", 5); // 将 "The worst" 的前 5 个字符复制到 "copy"
```

## 格式化输出
```c
sprintf(flower, "A %s in the hand is worth %d in the bush.", "bird", 10);
```

## 其他字符串函数
```c
char *strchr(const char *str, int ch); // 查找字符的第一次出现
char *strrchr(const char *str, int ch); // 查找字符的最后一次出现
char *strstr(const char *str1, const char *str2); // 查找子字符串的第一次出现
char *strtok(char *str, const char *delim); // 分割字符串

char str[] = "Hello, world! This is a test.";
const char delim[] = " ,.!"; // 分隔符：空格、逗号、点
char *token = strtok(str, delim);

while (token != NULL) {
    printf("Token: %s\n", token);
    token = strtok(NULL, delim);
}

size_t strspn(const char *str1, const char *str2); // 包含 str2 中字符的初始段长度
size_t strcspn(const char *str1, const char *str2); // 不包含 str2 中字符的初始段长度
char *strpbrk(const char *str1, const char *str2); // 查找 str2 中任意字符在 str1 中的第一次出现
char *strlwr(char *str); // 转换字符串为小写
char *strupr(char *str); // 转换字符串为大写
char *strrev(char *str); // 反转字符串
char *strset(char *str, int ch); // 将字符串中的所有字符设置为 ch
char *strnset(char *str, int ch, size_t n); // 将字符串的前 n 个字符设置为 ch
char *strerror(int errnum); // 返回错误信息字符串
size_t strlen(const char *str); // 获取字符串长度
char *strdup(const char *str); // 复制字符串
```

## 结论
本文档概述了 C 语言中各种字符串处理函数，包括输入/输出函数、字符串操作、比较和其他实用函数。
