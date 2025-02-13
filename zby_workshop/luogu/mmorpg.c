#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    char** yesterday = (char**)malloc(n * sizeof(char*));
    char** today = (char**)malloc(m * sizeof(char*));
    char** news = (char**)malloc(k * sizeof(char*));
    int* explored = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        yesterday[i] = (char*)malloc(100 * sizeof(char));
        scanf("%s", yesterday[i]);
    }
    qsort(yesterday, n, sizeof(char*), compare);  
    for (int i = 0; i < m; i++) {
        today[i] = (char*)malloc(100 * sizeof(char));
        scanf("%s", today[i]);
        char** found = bsearch(&today[i], yesterday, n, sizeof(char*), compare);
        if (found) explored[found - yesterday] = 1;
    }
    for (int i = 0; i < k; i++) {
        news[i] = (char*)malloc(100 * sizeof(char));
        scanf("%s", news[i]);
    }
    int result_size = 0;
    for (int i = 0; i < n; i++) result_size += !explored[i];
    result_size += k;

    char** result = (char**)malloc(result_size * sizeof(char*));
    int index = 0;

    for (int i = 0; i < n; i++) {
        if (!explored[i]) {
            result[index] = yesterday[i]; 
            index++;
        }
    }
    for (int i = 0; i < k; i++) {
        result[index++] = news[i];
    }

    qsort(result, result_size, sizeof(char*), compare);
    for (int i = 0; i < result_size; i++) {
        printf("%s\n", result[i]);
    }
    for (int i = 0; i < n; i++) free(yesterday[i]);
    for (int i = 0; i < m; i++) free(today[i]);
    for (int i = 0; i < k; i++) free(news[i]);
    free(yesterday);
    free(today);
    free(news);
    free(explored);
    free(result);
    return 0;
}