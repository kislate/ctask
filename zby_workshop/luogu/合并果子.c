#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005

int heap[MAXN];
int size = 0;

//小根堆插入
void push(int x) {
    int i = ++size;
    heap[i] = x;
    while (i > 1 && heap[i] < heap[i / 2]) {
        int t = heap[i]; heap[i] = heap[i / 2]; heap[i / 2] = t;
        i /= 2;
    }
}

//小根堆弹出堆顶
int pop() {
    int top = heap[1];
    heap[1] = heap[size--];
    int i = 1;

    while (1) {
        int smallest = i;
        int l = i * 2, r = i * 2 + 1;

        if (l <= size && heap[l] < heap[smallest]) smallest = l;
        if (r <= size && heap[r] < heap[smallest]) smallest = r;

        if (smallest == i) break;

        int t = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = t;

        i = smallest;
    }
    return top;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        push(x);
    }

    long long ans = 0;

    while (size > 1) {
        int a = pop();
        int b = pop();
        ans += a + b;
        push(a + b);
    }

    printf("%lld\n", ans);
    return 0;
}
