#include <stdio.h> 
#include <stdlib.h>
char*strcopy(char*, const char *); 
int main(void) 
{
    char *s1,*s2,*s3; 
    s1 = (char*)malloc(50); //若不分配空间，则指针指向未知，很危险
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
	free(s3);//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    return 0; 
}
/*将字符串s复制给字符串t，并且返回串t的首地址*/ 
char *strcopy (char *t,const char *s) 
{
	char *p=t; 
    while(*t++ = *s++); 
    return p; 
}
//Q:Q:为何头歌不过，无语。。。。。。。。。。（但dev-c++能运行）
//A:free(s3)->free过的再free