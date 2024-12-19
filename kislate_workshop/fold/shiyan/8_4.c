#include<stdio.h>
#include<stdlib.h>..
int fcopy(char * , char *);
int main(int argc, char *argv[])
{
    int i;
    if(argc<3)
    {
        printf("The command syntax is incorrect.fcopy[source filename] [target filename]\n");
        exit(0);
    }
    if(!fcopy(argv[1],argv[2]))
        printf("No such a file:%s or %s \n",argv[1],argv[2]);
    return 0;
}
int fcopy(char *sourcename, char *targetname)
{
    char c;
    FILE *fp1, *fp2;
    if (!(fp1 = fopen(sourcename, "r")))
        return 0;
    if (!(fp2 = fopen(targetname, "w")))
        return 0;
    while ((c = fgetc(fp1)) != EOF)
        putc(c, fp2);
    fclose(fp1);
    fclose(fp2);
    return 1;
}

