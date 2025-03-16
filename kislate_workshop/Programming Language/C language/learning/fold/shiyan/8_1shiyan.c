#include<stdio.h>
int main(void)
{
    short a =0x253f,b =0x7b7d;
    char ch;
    FILE *fp1,*fp2;
    fp1 = fopen("test1.bin","wb+");
    fp2 = fopen("test2.exe","w+");
    fwrite(&a,sizeof(short),1,fp1);
    fwrite(&b,sizeof(short),1,fp1);
    fprintf(fp2,"%hx %hx",a,b);

    rewind(fp1);
    rewind(fp2);
    while((ch = fgetc(fp1))!=EOF)
        putchar(ch);
    while((ch = fgetc(fp2))!=EOF)
        putchar(ch);
    putchar(10);
    fclose(fp1);
    fclose(fp2);
    return 0;
}