#include <stdio.h>
#include <stdlib.h>

void divide(long long a, int* num, int* count, int* sum) {
    *sum = 0;
    if (a % 2 == 0) {
        num[*sum] = 2;
        count[*sum] = 0;
        while (a % 2 == 0) {
            a /= 2;
            count[*sum]++;
        }
        (*sum)++;
    }
    for (long long i = 3; i * i <= a; i += 2) {
        if (a % i == 0) {
            num[*sum] = i;
            count[*sum] = 0;
            while (a % i == 0) {
                a /= i;
                count[*sum]++;
            }
            (*sum)++;
        }
    }

    if (a > 1) {
        num[*sum] = a;
        count[*sum] = 1;
        (*sum)++;
    }
}

long long calculate(int* num, int* count, int sum, int k) {
    long long result = 1;
    for (int i = 0; i < sum; i++) {
        if (count[i] >= k) {
            long long factor = 1;
            for (int j = 0; j < count[i]; j++) {
                factor *= num[i];
            }
            result *= factor;
        }
    }
    return result;
}

int main() {
    int q;
    scanf("%d", &q);

    long long* a = (long long*)malloc(sizeof(long long) * q);
    int* k = (int*)malloc(sizeof(int) * q);
    int* num = (int*)malloc(sizeof(int) * 9999);
    int* count = (int*)malloc(sizeof(int) * 9999);
    int sum;
    for (int i = 0; i < q; i++) {
        scanf("%lld %d", &a[i], &k[i]);
    }
    for (int i = 0; i < q; i++) {
        divide(a[i], num, count, &sum);
        printf("%lld\n", calculate(num, count, sum, k[i]));
    }
    free(a);
    free(k);
    free(num);
    free(count);
    return 0;
}