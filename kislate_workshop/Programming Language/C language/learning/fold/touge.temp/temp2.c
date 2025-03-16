/*
任务描述
本关任务：编写函数，将三个文件进行复制拼接到一个新文件中。

相关知识（略）
编程要求
编写相应的函数，将三个文件进行复制拼接。

测试说明
平台会对你编写的代码进行测试：

测试结果为三个文件内容拼接即可，文件内容之间用回车分隔。

开始你的任务吧，祝你成功！*/
#include<stdio.h>

/*********************************************************************************
  完成函数，连接filename1、filename2 和 filename3 三个文件的内容到 filename 文件中
  先连接file1，再连接file2，最后连接file3
  ********************************************************************************/
void connect(char *filename,char *filename1,char *filename2,char *filename3)
{
	// 请在此处编辑您的代码
	/********** Begin **********/
    FILE *fp1,*fp2,*fp3,*fp;
    char c;
    if(!(fp1 = fopen(filename1,"r")))
        return;
    if(!(fp2 = fopen(filename2,"r")))
        return;
    if(!(fp3 = fopen(filename3,"r")))
        return;
    if(!(fp = fopen(filename,"w")))
        return;
    while((c = fgetc(fp1))!= EOF)
        putc(c,fp);
    while((c = fgetc(fp2)) != EOF)
        putc(c,fp); 
    while((c = fgetc(fp3)) != EOF)
        putc(c,fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp);
	/********** End **********/
   
}