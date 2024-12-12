#include <stdio.h>

char u[] = "UVWXYZ", v[] = "xyz";

struct T {
    int x;
    char c;
    char *t;
} a[] = { {11, 'A', u}, {100, 'B', v} }, *p = a;

void printArr(char *arr) {
    while (*arr) {
        putchar(*arr++);
    }
}

int main(void) {
    int n;
    scanf("%d", &n);
    switch (n) {
        case 1:
            printf("%d", (++p)->x);
            break;
        case 2:
            printf("%c", (++p)->c);
            break;
        case 3:
            printArr(p++->t);
            printArr(p->t);
            break;
        case 4:
            printArr((++p)->t);
            break;
        case 5:
            printArr((++p)->t);
            break;
        case 6:
            printArr(++p->t);
            break;
    }
    return 0;
}
