#include<stdio.h>
int main(void){
    int i,r;
    char s1[80] = "bus",s2[80] = "book";
    for(i=r=0;s1[i]!='\0'&&s2[i]!='\0';i++)
    {
        if(s1[i] == s2[i])
            i++;
        else
            {
                r=s1[i]-s2[i];
                break;
            } 
    }
    printf("%d\n",r);
    return 0;
}