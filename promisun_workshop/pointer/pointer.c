#include <stdio.h> 
#include <stdlib.h>
char*strcopy(char*, const char *); 
int main(void) 
{
    char *s1,*s2,*s3; 
    s1 = (char*)malloc(50); //������ռ䣬��ָ��ָ��δ֪����Σ��
    s2 = (char*)malloc(50); 
    s3 = (char*)malloc(50); 
    scanf("%s",s2); 
    strcopy(s1,s2); 
    scanf("%s",s2);
    printf("%s\n",s1); 
    s3=strcopy(s1,s2); 
    printf("%s",s3);
    free(s1); //�ͷ�
    free(s2);
	free(s3);
    return 0; 
}
/*���ַ���s���Ƹ��ַ���t�����ҷ��ش�t���׵�ַ*/ 
char *strcopy (char *t,const char *s) 
{
	char *p=t; 
    while(*t++ = *s++); 
    return p; 
}
