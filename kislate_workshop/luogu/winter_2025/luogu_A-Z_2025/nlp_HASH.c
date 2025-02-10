#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 21
#define MAX_SENTENCE_LEN 50001
#define HASH_SIZE 10007  // 选择一个较大的质数减少冲突

// 哈希表节点结构
typedef struct HashNode {
    char key[MAX_STR_LEN];
    int value;
    struct HashNode *next;
} HashNode;

// 哈希函数（djb2算法，经典字符串哈希）
unsigned long hash_func(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % HASH_SIZE;
}

// 插入键值对到哈希表
void hash_insert(HashNode **table, const char *key, int value) {
    unsigned long index = hash_func(key);
    HashNode *node = (HashNode*)malloc(sizeof(HashNode));
    strcpy(node->key, key);
    node->value = value;
    node->next = table[index]; // 头插法
    table[index] = node;
}

// 从哈希表中查找键对应的值（找到返回值，否则返回-1）
int hash_search(HashNode **table, const char *key) {
    unsigned long index = hash_func(key);
    HashNode *current = table[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return -1; // 题目保证存在，这里仅示例
}

// 释放哈希表内存
void free_hash_table(HashNode **table) {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *current = table[i];
        while (current != NULL) {
            HashNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main(void) {
    int n, m;
    scanf("%d%d", &n, &m);

    // 初始化哈希表
    HashNode **hash_table = (HashNode**)calloc(HASH_SIZE, sizeof(HashNode*));

    // 读取字典到哈希表
    for (int i = 0; i < n; i++) {
        char key[MAX_STR_LEN];
        int value;
        scanf("%s%d", key, &value);
        hash_insert(hash_table, key, value);
    }

    while (getchar() != '\n'); // 清除换行符

    // 处理每个句子
    for (int i = 0; i < m; i++) {
        char sentence[MAX_SENTENCE_LEN];
        fgets(sentence, MAX_SENTENCE_LEN, stdin);
        char output[MAX_SENTENCE_LEN] = {0};
        char *start = sentence;

        while (*start) {
            char *p = strchr(start, '{');
            if (!p) {
                strcat(output, start);
                break;
            }
            strncat(output, start, p - start);

            char *q = strchr(p, '}');
            if (!q) {
                strcat(output, p);
                break;
            }

            // 提取{}内的key
            char tmp[MAX_STR_LEN];
            int len = q - p - 1;
            strncpy(tmp, p + 1, len);
            tmp[len] = '\0';

            // 哈希查找
            int value = hash_search(hash_table, tmp);
            if (value != -1) { // 题目保证存在
                char num_str[12];
                sprintf(num_str, "%d", value);
                strcat(output, num_str);
            }

            start = q + 1;
        }

        printf("%s", output);
    }

    // 释放内存
    free_hash_table(hash_table);
    free(hash_table);

    return 0;
}