/*任务描述
本关任务：修改2.(1)的程序，在显示文本的过程中对每一行加一个行号，同时，设计一个显示控制参数/p，使得每显示5行（一屏）就暂停，当用户按下任何一个键，例如"q"就继续显示下一屏。

编程要求
根据提示，在右侧编辑器修改代码。

测试说明
平台会对你编写的代码进行测试：

测试输入：
cat test1.txt /p      （控制台命令）
q                     （运行时输入）
预期输出：
1 1234567
2 abcdefg
3 !@#$%^&
4 1234567
5 abcdefg

开始你的任务吧，祝你成功！*/
#include<stdio.h>

int main(int argc, char* argv[])
{
	FILE * fp;
	if(argc<=2){
		printf("Arguments error!\n");
		exit(-1);
	}
	if((fp=fopen(argv[1],"r"))==NULL){      /* fp指向filename */
		printf("Can't open %s file!\n", argv[1]);
		exit(-1);
	}
	// while(!feof(fp))             
	// 	putchar(fgetc(fp));            /* 向显示器中写从filename中读取的字符 */ 
	// fclose(fp); 
    char line[100];                       /* 关闭filename */ 
    while(fgets(line,100,fp))
    {
        static int count = 0;
        count++;
        printf("%d %s",count,line);
        if(count%5==0)
        {
            count =1;
            char c;
            while((c = getchar()) != 'q')
                break;
        }
    }
	return 0;
}