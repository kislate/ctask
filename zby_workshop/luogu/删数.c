#include <stdio.h>
#include <string.h>

int main() {
    char n[250];
    int k;
    scanf("%s", n);
    scanf("%d", &k);

    int len = strlen(n);
    char new[250];
    int top = -1;//栈为空时 top = -1

    for (int i = 0; i < len; i++) {
        char cur = n[i];
        while (top >= 0 && new[top] > cur && k > 0) {
            top--;
            k--;
        }

        new[++top] = cur;
	}//确保栈内单调递增

    //若还没删完k，则数字递增，从最后删
    while (k > 0) {
        top--;
        k--;
    }

    //删除前导零
    int start = 0;
    while (start <= top && new[start] == '0') start++;

    //若删光或全是 0
    if (start > top) {
        printf("0\n");
        return 0;
    }

    //输出结果
    for (int i = start; i <= top; i++) {
        putchar(new[i]);
    }

    return 0;
}
