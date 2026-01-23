#include <stdio.h>

int main(){
    char stack[50]={0};
    char c;
    int count=0,top=0,flag=0;//flag标记是否找到相同字母值

    while((c=getchar())!=EOF){
        if(c=='\n') break;
        if(stack[top]==0) {
            stack[top]=c;
            continue;
        }//初始栈为空时首字母入栈
        for(int i=top;i>=0;i--){
            if(stack[i]==c) {
                count=count+top-i;//相同字母间夹杂的其他字母出栈，必须从后面即top往下遍历找相同值
                top=i;
                flag=1;
            }
        }
        if(!flag) stack[++top]=c;//未找到直接入栈
        flag=0;
    }
    count=count+top+1;//加上最后留在栈中的字母

    printf("%d",count);
    return 0;
}