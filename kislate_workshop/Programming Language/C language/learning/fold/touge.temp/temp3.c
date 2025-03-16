/*任务描述
本关任务：参考实验指导书P225-226页内容，功能要求是，通过命令行参数将指定的文本文件内容显示在屏幕上。给出的源程序中存在一些逻辑错误，对程序进行修改、调试，使之能够正确完成指定任务。
命令的格式是：D:>cat filename
编程要求
根据提示，在右侧编辑器修改代码。

测试说明
平台会对你编写的代码进行测试：

测试命令行：cat test1.txt
预期输出：
123456
1234567
abcdefg
!@#$%^&
1234567
abcdefg
!@#$%^&
1234567
abcdefg
!@#$%^&

开始你的任务吧，祝你成功！*/
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[])
{
	FILE * fp;
	if(argc!=2){
		printf("Arguments error!\n");
		exit(-1);
	}
	if((fp=fopen(argv[1],"r"))==NULL){      /* fp指向filename */
		printf("Can't open %s file!\n", argv[1]);
		exit(-1);
	}
    char ch;
	while((ch=fgetc(fp))!=EOF)//不能直接这么用因为在尝试读取文件并且文件到达文件末尾之后才会返回真，因此，可能会多读取一次；             
		putchar(ch);            /* 向显示器中写从filename中读取的字符 */ 
	fclose(fp);                        /* 关闭filename */ 
	return 0;
}
