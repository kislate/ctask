#include <stdio.h>
#include <stdlib.h>
int isprime(int n) {
    int k, limit;
    if (n == 2) return 1;
    if (!(n % 2)) return 0;
    limit = n / 2;
    for (k = 3; k <= limit; k += 2)
        if (!(n % k)) return 0;
    return 1;
}

void find(int* nums, int n, int k, int start, int* combination, int cot, int* count) {
    if (cot == k) {
        int sum = 0;
        for (int i = 0; i < k; i++) {
            sum += combination[i];
        }
        if (isprime(sum)) {
            (*count)++;
        }
        return;
    }

    for (int i = start; i < n; i++) {
        combination[cot] = nums[i];
        find(nums, n, k, i + 1, combination, cot + 1, count);
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int *nums = (int *)malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    int *combination = (int *)malloc(sizeof(int)*k);
    int count = 0;

    find(nums, n, k, 0, combination, 0, &count);

    printf("%d\n", count);
    free(nums);
    free(combination);
    return 0;
}
