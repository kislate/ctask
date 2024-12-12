/*测试说明
平台会对你编写的代码进行测试，比对你输出的数值与实际正确数值，只有所有数据全部计算正确才能通过测试，以下是对程序的检查的测试说明：

测试输入：
type_c test1.c
预期输出：
文件test1.c的内容及行号

测试输入：

type_c /p test1.c
q
q
预期输出：
文件test1.c的内容分屏显示

注意：此处的输出，分屏后，行号从1重新标注。

测试输入：
type test1.c
预期输出：
指令错误

开始你的任务吧，祝你成功！*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_file(const char *filename, int paginate) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("指令错误\n");
        return;
    }

    char line[256];
    int line_number = 1;
    int page_line_count = 0;
    while (fgets(line, sizeof(line), file)) {
        if (paginate && page_line_count == 10) {
            printf("q\n");
            page_line_count = 0;
            line_number = 1;
        }
        printf("%d: %s", line_number++, line);
        page_line_count++;
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("指令错误\n");
        return 1;
    }

    int paginate = 0;
    char *filename;

    if (argc == 3 && strcmp(argv[1], "/p") == 0) {
        paginate = 1;
        filename = argv[2];
    } else if (argc == 2) {
        filename = argv[1];
    } else {
        printf("指令错误\n");
        return 1;
    }

    display_file(filename, paginate);
    return 0;
}
