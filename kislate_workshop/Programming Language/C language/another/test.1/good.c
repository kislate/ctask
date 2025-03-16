#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uthash.h>

#define MAX_STR_LEN 21
#define MAX_SENTENCE_LEN 50001

typedef struct {
    char key[MAX_STR_LEN];
    int value;
    UT_hash_handle hh;
} HashItem;

void free_memory(char **str, int n, int *num, HashItem *hash_table) {
    for (int i = 0; i < n; i++) {
        free(str[i]);
    }
    free(str);
    free(num);

    HashItem *current_item, *tmp;
    HASH_ITER(hh, hash_table, current_item, tmp) {
        HASH_DEL(hash_table, current_item);
        free(current_item);
    }
}

int main(void) {
    int n, m;
    scanf("%d%d", &n, &m);

    char **str = (char **)malloc(sizeof(char *) * n);
    int *num = (int *)malloc(sizeof(int) * n);
    if (str == NULL || num == NULL) {
        fprintf(stderr, "\"**str or *num\" Memory allocation failed\n");
        return 1;
    }

    HashItem *hash_table = NULL;

    for (int i = 0; i < n; i++) {
        str[i] = (char *)malloc(sizeof(char) * MAX_STR_LEN);
        if (str[i] == NULL) {
            fprintf(stderr, "\"*str\" Memory allocation failed\n");
            return 1;
        }
        scanf("%s%d", str[i], num + i);

        HashItem *item = (HashItem *)malloc(sizeof(HashItem));
        strcpy(item->key, str[i]);
        item->value = num[i];
        HASH_ADD_STR(hash_table, key, item);
    }

    char *sentence = (char *)malloc(sizeof(char) * MAX_SENTENCE_LEN);
    if (sentence == NULL) {
        fprintf(stderr, "\"sentence\" Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < m; i++) {
        if (fgets(sentence, MAX_SENTENCE_LEN, stdin) == NULL) {
            fprintf(stderr, "Error reading sentence\n");
            return 1;
        }
        sentence[strcspn(sentence, "\n")] = 0;

        char *output = (char *)malloc(sizeof(char) * MAX_SENTENCE_LEN);
        if (output == NULL) {
            fprintf(stderr, "\"output\" Memory allocation failed\n");
            return 1;
        }
        output[0] = '\0';

        char *start = sentence;
        while (*start) {
            char *q = strchr(start, ' ');
            if (q == NULL) q = start + strlen(start);

            char word[MAX_STR_LEN];
            strncpy(word, start, q - start);
            word[q - start] = '\0';

            HashItem *item;
            HASH_FIND_STR(hash_table, word, item);
            if (item) {
                char num_str[12];
                sprintf(num_str, "%d", item->value);
                strcat(output, num_str);
            }

            start = q + 1;
        }

        printf("%s", output);
        free(output);
    }

    free(sentence);
    free_memory(str, n, num, hash_table);
    return 0;
}