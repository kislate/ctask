/*任务描述
本关任务：参考实验指导书P226,3.(2)。从键盘输入10个单精度浮点数，以二进制形式存入文件float.dat中（将此功能定义成函数）。再从文件中读出这10个单精度浮点数,把每个单精度浮点数，按每个字节的二进制形式显示在屏幕上（将此功能定义成函数）。

根据提示，在右侧编辑器补充代码。

测试说明
平台会对你编写的代码进行测试：

测试输入：1.25，2.25，3.75，4.465，101.25，102.75，30.68，42.85，58.65，102.25；
预期输出：
00111111101000000000000000000000
01000000000100000000000000000000
01000000011100000000000000000000
01000000100011101110000101001000
01000010110010101000000000000000
01000010110011011000000000000000
01000001111101010111000010100100
01000010001010110110011001100110
01000010011010101001100110011010
01000010110011001000000000000000

开始你的任务吧，祝你成功！*/
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
    FILE *fp;
    if(!(fp = fopen("float.dat","wb+")))
    {
        printf("Can't open file!\n");
        exit(-1);
    }
    float f;
    for(int i = 0;i<10;i++){
        scanf("%f",&f);
        fwrite(&f,sizeof(float),1,fp);
        fputc('\n',fp);
    }
    rewind(fp);
    float f1;
    while(fread(&f1,sizeof(float),1,fp))
    {
        unsigned char *p =(unsigned char *)&f1;
        for(int i = 0;i<sizeof(float);i++)
        {
            for(int j = 0;j<8;j++)
            {
                printf("%d",p[i]>>j&1);
            }
        }
    }
    fclose(fp);
    return 0;
}

#include<stdlib.h>

int main(int argc,char *argv[])
{
    FILE *fp;
    if(!(fp = fopen("float.dat","wb+")))
    {
        printf("Can't open file!\n");
        exit(-1);
    }
    float f;
    for(int i = 0;i<10;i++){
        scanf("%f",&f);
        fwrite(&f,sizeof(float),1,fp);
        fputc('\n',fp);//这个东西要删掉，不然你就会存入一些奇怪的东西
    }
    rewind(fp);
    float f1;
    while(fread(&f1,sizeof(float),1,fp))
    {
        unsigned char *p =(unsigned char *)&f1;
        for(int i = sizeof(float)-1;i>=0;i--)
        {           
            for(int j = 7;j>=0;j--)
            {
                printf("%d",p[i]>>j&1);
            }
        }
        putchar('\n');
    }
    fclose(fp);
    return 0;
}