# C语言的文件操作

#### *文件指针*
- 每个被使用的的文件都开辟了一个相应的文件信息区，用来存放文件的相关信息。
- 该结构体类型由系统声明，取名为FILE。
```c
    struct _iobuf{
        char* ptr;
        int _cnt;
        char* _base;
        int _flag;
        int _charbuf;
        int _bufsiz;
        char* _tmpfname;
    }
```

- 不同的C编译器的FILE类型包含的内容不完全相同，但是大同小异。
- 每当打开一个文件的时候，系统会根据文件的情况自动创建一个FILE结构的变量，并且填充其中的信息，使用者不必关心细节。
- 一般来说通过一个FILE的指针来维护这个FILE结构的变量（通过FILE类型的指针找到文件信息区的起始地址），这样使用起来更加方便。
  
```c
    FILE* pf;//文件指针变量
```
- 定义pf是一个指向FILE类型的指针变量。可以使pf指向某个文件的文件信息区（是一个结构体变量）。通过该文件按信息区中的信息就能够访问文件。也就是所，通过文件指针能够找到与它关联的文件。

### 文件操作--打开和关闭

### 文件打开模式

#### 1.fopen函数：
```c
    FILE*pf =fopen("#你的文件路径（相对或者绝对）"，"(这里就是下面的参数)")
```

- 这个函数的返回值是一个FILE类型的指针，在文件成功打开后返回此文件信息区的起始位置，打开失败则返回一个NUll，所以使用fopen时要使用一个FILE类型的指针来接受其返回值。
  ```c
    	//打开
	FILE* pf = fopen("text.txt","w");//在这里面打文件路径的时候要转义（只要在引号里面都要转义）
	//判断是否打开成功
	if (pf == NULL)
	{
		perror("fopen");
		return 1;
	}
  ```
| 文件使用方式 | 含义 | 如果指定文件不存在 |
| ------------ | ---- | ------------------ |
| "r" (只读)   | 为了输入数据，打开一个已经存在的文本文件 | 出错 |
| "w" (只写)   | 为了输出数据，打开一个文本文件 | 建立一个新的文件 |
| "a" (追加)   | 向文本文件尾添加数据 | 建立一个新的文件 |
| "rb" (只读)  | 为了输入数据，打开一个二进制文件 | 出错 |
| "wb" (只写)  | 为了输出数据，打开一个二进制文件 | 建立一个新的文件 |
| "ab" (追加)  | 向一个二进制文件尾添加数据 | 出错 |
| "r+" (读写)  | 为了读和写，打开一个文本文件 | 出错 |
| "w+" (读写)  | 为了读和写，建一个新的文件 | 建立一个新的文件 |
| "a+" (读写)  | 打开一个文件，在文件尾进行读写 | 建立一个新的文件 |
| "rb+" (读写) | 为了读和写打开一个二进制文件 | 出错 |
| "wb+" (读写) | 为了读和写，新建一个新的二进制文件 | 建立一个新的文件 |
| "ab+" (读写) | 打开一个二进制文件，在文件尾进行读和写 | 建立一个新的文件 |
<p style="text-align: center;">注：当使用"w","wb","w+","wb+"打开文件时会清除文件原本存储的数据</p>
  
  - w+和w区别就是w+可以读一下。
  ```
在使用 "w+" 模式打开文件时，你可以在读和写之间切换，但需要注意文件指针的位置。
为了确保正确的读写操作，你可以使用 fflush、fseek 或 rewind 函数来调整文件指针
的位置。
  ```
  ```c
  #include <stdio.h>

int main() {
    // 以读写模式打开文件
    FILE *pf = fopen("text.txt", "w+");
    if (pf == NULL) {
        perror("fopen");
        return 1;
    }

    // 写入数据
    for (int i = 0; i < 26; i++) {
        fputc('a' + i, pf);
    }

    // 刷新输出缓冲区，确保数据写入文件
    fflush(pf);

    // 将文件指针移到文件开头
    rewind(pf);

    // 读取数据并打印
    char ch;
    while ((ch = fgetc(pf)) != EOF) {
        putchar(ch);
    }

    // 关闭文件
    if (fclose(pf) == EOF) {
        perror("fclose");
        return 1;
    }

    pf = NULL;
    return 0;
}
  ```
  ```c
  #include <stdio.h>//这里就是用fseek来改变指针的位置

int main() {
    // 以读写模式打开文件
    FILE *pf = fopen("text.txt", "w+");
    if (pf == NULL) {
        perror("fopen");
        return 1;
    }

    // 写入数据
    for (int i = 0; i < 26; i++) {
        fputc('a' + i, pf);
    }

    // 刷新输出缓冲区，确保数据写入文件
    fflush(pf);

    // 将文件指针移到文件开头
    fseek(pf, 0, SEEK_SET);

    // 读取数据并打印
    char ch;
    while ((ch = fgetc(pf)) != EOF) {
        putchar(ch);
    }

    // 关闭文件
    if (fclose(pf) == EOF) {
        perror("fclose");
        return 1;
    }

    pf = NULL;
    return 0;
}
  ```



### 2.fclose：
- 该函数返回的时，成功的话返回0，否则返回EOF；
  <p style="text-align: center; font-size: small;">注：当使用"w","wb","w+","wb+"以下就是使用示例</p>
```c
    int main()
{
	//打开
	FILE* pf = fopen("text.txt","w");
	//判断是否打开成功
	if (pf == NULL)
	{
		perror("fopen");
		return 1;
	}
	//关闭
	if (fclose(pf) == EOF)
	{
		//关闭失败
		perror("fclose");
		return 1;
	}
	pf = NULL;//记得把原本的文件指针置为NULL，避免野指针的产生。
	return 0;
}
```

## 文件的读写

### 1.顺序读写
| 功能           | 函数名   | 适用于       |
| -------------- | -------- | ------------ |
| 字符输入函数   | fgetc    | 所有输入流   |
| 字符输出函数   | fputc    | 所有输出流   |
| 文本行输入函数 | fgets    | 所有输入流   |
| 文本行输出函数 | fputs    | 所有输出流   |
| 格式化输入函数 | fscanf   | 所有输入流   |
| 格式化输出函数 | fprintf  | 所有输出流   |
| 二进制输入     | fread    | 文件         |
| 二进制输出     | fwrite   | 文件         |

  
  #### fputc:
  - 运用示例
  ```c
    int main()
{
	//打开
	FILE* pf = fopen("text.txt", "w");
	//判断是否打开成功
	if (pf == NULL)
	{
		perror("fopen");
		return 1;
	}
	//写入数据
	int i = 'a';
	for (i = 0; i < 26; i++)
	{
        fputc('a' + i, pf);
	}
	//关闭
	if (fclose(pf) == EOF)
	{
		//关闭失败
		perror("fclose");
		return 1;
	}
	pf = NULL;
	return 0;
}//这里就会打印出a-z;但是这里是不能读的，要w+才能读。
  ```

#### fgetc:
-这个函数成功读入数据的时候会返回读取字符的ASCII值，反之就会返回EOF（-1)值。
运用示例：
```c
int main()
{
	//打开
	FILE* pf = fopen("text.txt", "r");//此时读取文件要用"r"的方式打开
	//判断是否打开成功
	if (pf == NULL)
	{
		perror("fopen");
		return 1;
	}
	//读入数据
	int i;
	while ((i = fgetc(pf)) != EOF)
	{
		printf("%c ", i);
	}
	//关闭
	if (fclose(pf) == EOF)
	{
		//关闭失败
		perror("fclose");
		return 1;
	}
	pf = NULL;
	return 0;
}//这里也是把a-z都给打印了一遍。
```
#### fgets：
- 这个函数没有什么可以特别说明的，可以转步到string里面来学习。
- 成功后，该函数返回 str的头指针
如果在尝试读取字符时遇到文件结尾，则会设置 eof 指示符 。如果在读取任何字符之前发生这种情况，则返回的指针为空指针（并且 str 的内容保持不变）。
如果发生读取错误，则设置错误指示器 （ferror） 并返回空指针（但 str 所指向的内容可能已更改）
- 记住这玩意后面要留位置给\0;

### fprintf(这个函数可以向文件输出任何的数据，可以理解这个函数把文件给当作屏幕了)
- int fprintf(FILE* stream,const char*fomat,········);
- stream:接收指向所要输出文件的指针；
- fomat：接收将要输出数据的格式（和printf函数一样由%d,%x,%c,%s等等格式类型）
- 这个函数会返回输出的字节总数，否则返回一个负数并且报错；//这个负数没有明确表明是-1；
- 注意printf也会返回输出的字节总数，与此同时不会计数\0。
- 所以说printf和fprintf本质上是打的字符串，遇到了\0就会结束，不管这个东西是你手打的还是格式化输入的。
```c
struct S
{
	int age;
	char name[20];
	char sex[5];
};
int main()
{
	struct S L = { 20,"张三","男" };
	//打开
	FILE* pf = fopen("text.txt", "w");
	//判断是否打开成功
	if (pf == NULL)
	{
		perror("fopen");
		return 1;
	}
	//输入数据
	fprintf(pf, "%d %s %s", L.age, L.name, L.sex);
	//关闭
	if (fclose(pf) == EOF)
	{
		//关闭失败
		perror("fclose");
		return 1;
	}
	pf = NULL;
	return 0;//这里会发现，当你打开这个文件的时候里面多了“20 张三 男”
}
```

#### fscanf:
- int scanf(FILE * stream,const char * format,·····)
- stream:接收指向索要输入文件的指针
- format:接收将要输入数据的格式（和scanf函数一样由%d，%x，%c，%s等等格式类型）
- 至于后面都是一样的
*运行成功后，该函数返回所读取数据的个数（甚至为0），如果在读取时发生读取时读取错误或者达到文件的末尾，则会设置正确的指示器（feof或者ferror），而且，如果在成功读取任何数据之前发生任何一种情况，则返回EOF*
```c
struct S
{
	int age;
	char name[20];
	char sex[5];
};
int main()
{
	struct S s;
	//打开
	FILE* pf = fopen("text.txt", "r");
	//判断是否打开成功
	if (pf == NULL)
	{
		perror("fopen");
		return 1;
	}
	//输出数据
	fscanf(pf, "%d %s %s", &(s.age), s.name, s.sex);
	printf("%d %s %s", s.age, s.name, s.sex);//这里的打印就是20 张三 男
	//关闭
	if (fclose(pf) == EOF)
	{
		//关闭失败
		perror("fclose");
		return 1;
	}
	pf = NULL;
	return 0;
}
```
#### fwrite:
- s_size fwrite(const void *ptr,size_t size,size_ count,FILE* stream);
>ptr:接收指向所要输入数据的指针或者地址
>size:接收输出的每个数据的大小I（以字节为单位）
>count:所要输出数据的个数
>stream:接收指向所要输出文件的指针
- 成功运行返回输出的数据总数，如果此数字字与count参数不同，则写入错误会组织函数的完成。在这种情况下，将为流设置错误指示器(ferror),如果大小或计数为0，则该函数返回0，并且错误指示器保持不变。
```c
 struct S
{
	int age;
	char name[20];
	char sex[5];
};
int main()
{
	struct S L = { 20,"李四","女" };
	//打开
	FILE* pf = fopen("text.txt", "wb");//二进制输出时用wb
	//判断是否打开成功
	if (pf == NULL)
	{
		perror("fopen");
		return 1;
	}
	//输出数据
	fwrite(&L, sizeof(struct S), 1, pf);
	//关闭
	if (fclose(pf) == EOF)
	{
		//关闭失败
		perror("fclose");
		return 1;
	}
	pf = NULL;
	return 0;
}
  ```
  - 这里的文件是通过二进制的方式向文件输出，记事本中所读取的数据我们肉眼时看不懂的（因为它是以文本形式读取的）
  - 可以用fread来解决这个问题