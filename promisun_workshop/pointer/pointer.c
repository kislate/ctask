#include<stdio.h> 
char*strcopy(char*, const char *); 
int main(void) 
{
    char *s1,*s2,*s3; 
    scanf("%s",s2); 
    strcopy(s1,s2); 
    printf("%s\n",s1); 
    scanf("%s",s2);
    s3=strcopy(s1,s2); 
    printf("%s\n",s3);
    return 0; 
}
/*将字符串s复制给字符串t，并且返回串t的首地址*/ 
char *strcopy (char *t,const char *s) 
{
    while(*t++=*s++); 
    return (t); 
}