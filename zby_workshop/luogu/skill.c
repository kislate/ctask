#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a) - *((int*)b);
}

int find(int** skills, int n, int m, int k, int mid) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (skills[i][0] > mid) {
            int need = skills[i][0] - mid;
            if (need * skills[i][1] > m) {
                return 0;
            }
            sum += need * skills[i][1];
            if (sum > m) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    int** skills = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        skills[i] = (int*)malloc(2 * sizeof(int));
        scanf("%d %d", &skills[i][0], &skills[i][1]);
    }

    qsort(skills, n, sizeof(int*), compare);

    int low = k, high = 0;
    for (int i = 0; i < n; i++) {
        if (skills[i][0] > high) high = skills[i][0];
    }

    int result = high;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (find(skills, n, m, k, mid)) {
            result = mid;
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    printf("%d\n", result);
    for (int i = 0; i < n; i++) {
        free(skills[i]);
    }
    free(skills);
    return 0;
}