//这道题唯一告诉我的，python的性能确实差

#include <stdio.h>
#include <math.h>

void find_prime_Meaningless(long long num, int k) {
    long long ret = num;
    long long temp = num;
    long long origin = num;

    for (long long i = 2; i * i <= origin; i++) {
        long long count = 0;
        if (num % i == 0) { // 分解本身就会帮我们判断其是否是质数，所以无需判断
            while (num % i == 0) {
                count++;
                num /= i;
                temp /= i;
            }
            if (count < k) {
                ret = temp;
            } else {
                temp = ret;
            }
        }
    }
    if (num > 1) {
        ret /= num;
    }
    printf("%lld\n", ret);
}

int main(void) {
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        long long a, k;
        scanf("%lld %lld", &a, &k);
        find_prime_Meaningless(a, k);
    }
    return 0;
}



// 下面这个还是有点慢
// void find_prime_Meaningless(long long num, int k) {
//     long long ret = 1;
//     for(int i = 2; i * i <= num; i++){
//         long long count = 0;
//         for(; num % i == 0; count++, num /= i);
//         if(count >= k)
//         {
//             ret *= pow(i, count);
//         }
//     }
//     printf("%lld\n", ret);
// }