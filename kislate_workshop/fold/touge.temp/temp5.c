/*
任务描述
本关任务：编写一个程序replace，采用命令行的方式，用给定的字符串替换指定文件中的目标字符串，替换后保存在out.txt中。
  你不需要输出out.txt中的内容，由平台输出。

编程要求
根据提示，在右侧编辑器补充代码。

测试说明
平台会对你编写的代码进行测试，并输出out.txt中的内容：

测试命令行：
replace test1.txt you they 
（将文件test1.txt中的you替换成they ）

预期输出：
So they think we ought to wait here?
I will run they in if the bus isn't going into the town because of the snow today.
In a pinch, they could get home on foot.
they don't know the facts, so keep theyr mouth shut!
We have many patterns in stock for they to choose from.

开始你的任务吧，祝你成功！
*/
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
            fwrite(p, 1, match - p, fp2);//这里就是把它给绕过去
            fputs(argv[3], fp2);
            p = match + strlen(argv[2]);
        }
        fputs(p, fp2);
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}
