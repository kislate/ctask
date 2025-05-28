#include <stdio.h>

int main()
{
    FILE *fp = fopen("tryfile.txt", "w+");
    if(!fp)
    {
        perror("fopen");
        return 1;
    }
    for (int i = 0; i < 26; i++)
    {
        fputc('a'+ i,fp);
    }
    fputc('\n',fp);

    fflush(fp);//刷新缓冲区
    rewind(fp);//将文件指针重新指向文件开头

    if (fclose(fp) == EOF) 
    {
        perror("fclose");
        return 1;
    }

    fp = NULL;
    return 0;

}