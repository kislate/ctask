/*任务描述
本关任务：编写程序，设置指令type_c与type_c /p来获取.c文件中的内容，获取type_c+文件名指令时，显示文件中的C语言程序，并为每一行开头加上行号（行号从1开始标注）；获取type_c /p+文件名指令时，为每一行开头加上行号的同时，每10行显示一屏，再次获取字母q，则显示下一屏。（为简化程序，本次测试使用测试文件超过10行，且不用考虑文件格式错误）

文件路径为：src/step1_1/test1.c。

相关知识（略）
编程要求
在右侧编辑器中编写代码，按照任务描述中的要求完成任务。

测试说明
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
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
void display_file_with_line_numbers(const char *filename, int paginate) {
    FILE *file = fopen("src/step1_1/test1.c", "r");
    if (!file) {
        printf("无法打开文件 %s", filename);
        return;
    }

    char line[256];
    int line_number = 1;
    int line_count = 0;

    while (fgets(line, sizeof(line), file)) {
        printf("%d  %s", line_number++, line);
        if (paginate && ++line_count % 10 == 0) {
            line_number = 1;
            char c;
            while ((c = getchar()) != 'q')
            break;
        }
    }

    fclose(file);
}
int main()
{
	// 请在此处编辑您的代码
	/********** Begin **********/
    char command[256];
    fgets(command, sizeof(command), stdin);
    char *token = strtok(command, " \n");
    if (strcmp(token, "type_c") == 0) {
        token = strtok(NULL, " \n");
        if (token && strcmp(token, "/p") == 0) {
            token = strtok(NULL, " \n");
            if (token) {
                display_file_with_line_numbers(token, 1);
            } else {
                printf("指令错误");
            }
        } else if (token) {
            display_file_with_line_numbers(token, 0);
        } else {
            printf("指令错误");
        }
    } else {
        printf("指令错误");
    }
	/********** End **********/
	return 0; 
}