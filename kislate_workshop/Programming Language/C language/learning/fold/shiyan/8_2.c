#include<stdio.h>
#define M 10
#define N 10
int fcreate(char *);
int main()
{
    if(fcreate("H:\\vscode_all\\ctask\\kislate_workshop\\fold\\scr.txt"))
        printf("File created successfully\n");
    else
        printf("File creation failed\n");
    return 0;
}
int fcreate(char *filename)
{
    char StuNo[M][N];
    int score[M],i;
    FILE *fp;

    if(!(fp=fopen(filename,"w")))
    {
        return 0;
    }
    for(i=0;i<M;i++)
    {
        scanf("%s%d",StuNo[i],&score[i]);
        fprintf(fp,"%s %d\n",StuNo[i],score[i]);
    }
    fclose(fp);
    return 1;
}//这个程序完美