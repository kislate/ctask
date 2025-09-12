#ifndef CNFPARSER_H
#define CNFPARSER_H

typedef struct Clause {
    int *literals;
    int len;
    struct Clause *next;
} Clause;

typedef struct Formula {
    Clause *head;
    int var_num;
    int clause_num;
} Formula;

// 读取并解析CNF文件，返回Formula指针，失败返回NULL
Formula* parse_cnf(const char *filename);

// 打印CNF公式
void print_formula(Formula *F);

// 释放CNF内存
void free_formula(Formula *F);

#endif