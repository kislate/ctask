#include <stdio.h>
long long L;
int N, M;
long long D[50002];

int check(long long mid) {
    int removed = 0;//移出石头个数
    long long last = 0;//起点位置为0

    for (int i = 1; i <= N + 1; i++){
        if (D[i] - last < mid) {
            removed++;//距离不够，必须移除一个石头
            if (removed > M) return 0;
        }
        else {
            last = D[i]; 
        }
    }
    return 1;//可以达到 mid
}

int main() {
    scanf("%lld %d %d", &L, &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &D[i]);
    }

	D[N + 1] = L;//终点作最后一块石头

    long long left=1, right=L, len=0;

    while (left <= right) {
        long long mid = (left + right) / 2;
        //二分
        if (check(mid)) {
            len = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    printf("%lld\n",len);
    return 0;
}
