#include <stdio.h>
#include <unistd.h> // for sleep function

int main(void) {
    printf("First Page\n");
    sleep(2); // 延迟2秒
    printf("\033[2J\033[H"); // 清屏并移动光标到左上角
    printf("Second Page\n");
    return 0;
}