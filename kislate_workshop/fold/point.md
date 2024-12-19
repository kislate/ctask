在 **C 语言** 中，指针相减是合法的操作，并且这种操作会返回两个指针之间的元素个数。具体来说，当你有两个指向同一数组（或同一块内存区域）的指针时，指针相减会返回它们之间的元素个数（对于字符指针来说，就是字节数）。

在你的代码中，`match` 和 `p` 都是指向同一行字符串的指针，因此它们之间的差值是合法的，并且表示 `match` 和 `p` 之间的字符数（字节数）。

**代码解释：**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Arguments error!\n");
        exit(-1);
    }

    FILE *fp1, *fp2;
    if ((fp1 = fopen(argv[1], "r")) == NULL) {
        printf("Can't open %s file!\n", argv[1]);
        exit(-1);
    }
    if ((fp2 = fopen("out.txt", "w")) == NULL) {
        printf("Can't open out.txt file!\n");
        fclose(fp1);
        exit(-1);
    }

    char line[100];
    while (fgets(line, sizeof(line), fp1)) {
        char *p = line;
        char *match;
        while ((match = strstr(p, argv[2])) != NULL) {
            // 输出匹配之前的部分
            fwrite(p, 1, match - p, fp2);
            // 输出替换字符串
            fputs(argv[3], fp2);
            // 移动指针到匹配字符串之后
            p = match + strlen(argv[2]);
        }
        // 输出剩余部分
        fputs(p, fp2);
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}
```

1. `match = strstr(p, argv[2])`：`strstr` 函数返回指向第一次出现的子字符串 `argv[2]` 的指针。
2. `fwrite(p, 1, match - p, fp2)`：`match - p` 计算 `match` 和 `p` 之间的字符数，从 `p` 到 `match` 的字符被写入文件 `fp2`。
3. `fputs(argv[3], fp2)`：将替换字符串 `argv[3]` 写入文件 `fp2`。
4. `p = match + strlen(argv[2])`：将指针 `p` 移动到匹配字符串 `argv[2]` 之后，继续处理剩余内容。

指针相减返回的是两个指针之间的元素个数，对于字符指针，就是字节数。这在字符串替换处理中非常有用。

---

在 C 语言中，`fwrite` 函数并不区分二进制数据和文本数据，它直接将内存数据写入文件。区分二进制文件和文本文件的关键在于文件打开模式。

**文件打开模式：**

- **文本模式**：`"r"`、`"w"`、`"a"`、`"r+"`、`"w+"`、`"a+"`  
  在文本模式下，某些字符（如换行符）可能会被转换。例如，在 Windows 系统中，`\n` 会被转换为 `\r\n`。
- **二进制模式**：`"rb"`、`"wb"`、`"ab"`、`"rb+"`、`"wb+"`、`"ab+"`  
  在二进制模式下，数据将原样写入文件，没有任何转换。

**示例：**

- **文本写入：**

  ```c
  FILE *fp = fopen("example.txt", "w");
  ```

- **二进制写入：**

  ```c
  FILE *fp = fopen("example.bin", "wb");
  ```

**完整示例：**

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    // 文本模式写入
    FILE *text_fp = fopen("example.txt", "w");
    if (text_fp == NULL) {
        perror("Error opening text file");
        return EXIT_FAILURE;
    }
    fputs("Hello, World!\n", text_fp);
    fclose(text_fp);

    // 二进制模式写入
    FILE *binary_fp = fopen("example.bin", "wb");
    if (binary_fp == NULL) {
        perror("Error opening binary file");
        return EXIT_FAILURE;
    }
    int data = 12345;
    fwrite(&data, sizeof(int), 1, binary_fp);
    fclose(binary_fp);

    return 0;
}
```

在上述示例中：

- `example.txt` 以文本模式打开，写入了一行文本 `"Hello, World!\n"`。
- `example.bin` 以二进制模式打开，写入了一个整数 `12345`。

通过选择合适的文件模式，可以控制数据以文本形式或二进制形式写入文件。