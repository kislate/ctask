#ifndef CNFPARSER_H
#define CNFPARSER_H

typedef struct Clause {
    int* literals;//子句中的文字数组
    int len;//文字个数
    struct Clause* next;//链表
} Clause;

typedef struct Formula {
	Clause* head;//子句链表头
    int var_num;//变量总数
    int clause_num;//子句总数
} Formula;

// 读取并解析CNF文件，返回Formula指针，失败返回NULL
Formula* parse_cnf(const char* filename);

// 打印CNF
void print_formula(Formula* F);

// 释放CNF内存
void free_formula(Formula* F);

#endif
