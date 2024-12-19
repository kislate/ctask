/*
任务描述
本关任务：利用文件操作重写实验六程序设计第(4)题。原始矩阵数据存放在当前目录下的文本文件matrix.in中，文件的第一行是两个整数n和m，表示矩阵的行数n和列数m，接下来的n行，每行有m个整数，表示矩阵数据。要求从matrix.in读数据，旋转后的矩阵输出到当前目录下的文本文件matrix.out中，该文件有m行，每行有n个整数。
   你不需要输出matrix.out中的内容，由平台输出。

编程要求
根据提示，在右侧编辑器补充代码。

测试说明
平台会对你编写的代码进行测试，并输出matrix.out中的内容：
测试输入：
src/step6/matrix1.in

预期输出：
3 4
5 2
1 3

开始你的任务吧，祝你成功！
*/
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
    FILE *fp1,*fp2;
    if(argc!=1)
    {
        printf("Arguments error!\n");
        exit(-1);
    }

    if(!(fp1 = fopen("argv[0]","r")))
    {
        printf("Can't open file!\n");
        exit(-1);
    }

    if(!(fp2 = fopen("matrix.out","w")))
    {
        printf("Can't open file!\n");
        fclose(fp1);
        exit(-1);
    }
    int n,m;
    fscanf(fp1,"%d %d",&n,&m);
    int matrix[100][100];
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<m;j++)
        {
            fscanf(fp1,"%d",&matrix[i][j]);
        }
    }
    for(int i = m-1;i>=0;i--)
    {
        for(int j = 0;j<n;j++)
        {
            fprintf(fp2,"%d",matrix[j][i]);
            if(j!=n-1)
                fputs(' ',fp2);
        }
        fprintf(fp2,"\n");
    }
    fclose(fp1);
    fclose(fp2);
}