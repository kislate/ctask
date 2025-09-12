#include<stdio.h>
#include<stdlib.h>
void shuru(FILE*fp)
{
    float f;
    for(int i = 0;i<10;i++){
        scanf("%f",&f);
        fwrite(&f,sizeof(float),1,fp);
    }
}
void print(FILE*fp)
{
    float f1;
    while(fread(&f1,sizeof(float),1,fp))
    {
        unsigned char *p =(unsigned char *)&f1;
        for(int i = sizeof(float)-1;i>=0;i--)
        {
            for(int j =7;j>=0;j--)
            {
                printf("%d",p[i]>>j&1);
            }
        }
        printf("\n");
    }
}
int main(int argc,char *argv[])
{
    FILE *fp;
    if(!(fp = fopen("float.dat","wb+")))
    {
        printf("Can't open file!\n");
        exit(-1);
    }
    shuru(fp);
    rewind(fp);
    print(fp);
    fclose(fp);
    return 0;
}