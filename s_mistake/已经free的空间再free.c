#include <stdio.h> 
#include <stdlib.h>
char*strcopy(char*, const char *); 
int main(void) 
{
    char *s1,*s2,*s3; 
    s1 = (char*)malloc(50); //若分配空间，则指针指向未知，很危险
    s2 = (char*)malloc(50); 
    s3 = (char*)malloc(50); 
    scanf("%s",s2); 
    strcopy(s1,s2); 
    scanf("%s",s2);
    printf("%s\n",s1); 
    s3=strcopy(s1,s2); 
    printf("%s",s3);
    free(s1); //释放
    free(s2);
	free(s3);//注意，这里指针的位置已经改变了
    return 0; 
}
/*将字符串s复制给字符串t，并且返回串t的首地址*/ 
char *strcopy (char *t,const char *s) 
{
	char *p=t; 
    while(*t++ = *s++); 
    return p; 
}

