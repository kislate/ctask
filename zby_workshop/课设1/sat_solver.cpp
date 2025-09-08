#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ===== 数据结构定义 =====
typedef struct Clause {
    int *literals;      // 子句中的文字数组
    int len;            // 子句长度
    struct Clause *next;
} Clause;

typedef struct Formula {
    Clause *head;       // 子句链表头
    int var_num;        // 变元数
    int clause_num;     // 子句数
} Formula;

// ===== CNF解析模块 =====
//CNF文件的读取
Formula* parse_cnf(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { printf("无法打开文件\n"); return NULL; }
    Formula *F = (Formula*)malloc(sizeof(Formula));
    F->head = NULL;
    F->var_num = 0;
    F->clause_num = 0;
    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        if (line[0] == 'c') continue; // 注释
        if (line[0] == 'p') {
            sscanf(line, "p cnf %d %d", &F->var_num, &F->clause_num);
            continue;
        }
        // 解析子句
        int lits[1024], cnt = 0, x;
        char *p = line;
        while (sscanf(p, "%d", &x) == 1 && x != 0) {
            lits[cnt++] = x;
            while (*p && *p != ' ') p++;
            while (*p == ' ') p++;
        }
        if (cnt > 0) {
            Clause *cl = (Clause*)malloc(sizeof(Clause));
            cl->literals = (int*)malloc(cnt * sizeof(int));
            memcpy(cl->literals, lits, cnt * sizeof(int));
            cl->len = cnt;
            cl->next = F->head;
            F->head = cl;
        }
    }
    fclose(fp);
    return F;
}

// ===== 公式遍历输出（验证用） =====
//CNF公式打印
void print_formula(Formula *F) {
    Clause *cl = F->head;
    int idx = 1;
    while (cl) {
        printf("Clause %d: ", idx++);
        for (int i = 0; i < cl->len; i++)
            printf("%d ", cl->literals[i]);
        printf("0\n");
        cl = cl->next;
    }
}

// ===== DPLL算法核心 =====
// 赋值数组：1为真，-1为假，0为未赋值
int DPLL(Formula *F, int *assign, int var_num);

// 单子句传播
int unit_propagate(Formula *F, int *assign, int var_num) {
    int changed = 1;
    while (changed) {
        changed = 0;
        Clause *cl = F->head;
        while (cl) {
            int unassigned = 0, last_lit = 0, satisfied = 0;
            for (int i = 0; i < cl->len; i++) {
                int lit = cl->literals[i];
                int v = abs(lit);
                if (assign[v] == 0) { unassigned++; last_lit = lit; }
                else if ((assign[v] == 1 && lit > 0) || (assign[v] == -1 && lit < 0)) {
                    satisfied = 1; break;
                }
            }
            if (!satisfied && unassigned == 1) {
                int v = abs(last_lit);
                assign[v] = last_lit > 0 ? 1 : -1;
                changed = 1;
            }
            cl = cl->next;
        }
    }
    return 1;
}

// 判断公式是否已满足或有空子句
int check_formula(Formula *F, int *assign) {
    Clause *cl = F->head;
    while (cl) {
        int satisfied = 0, unassigned = 0;
        for (int i = 0; i < cl->len; i++) {
            int lit = cl->literals[i];
            int v = abs(lit);
            if (assign[v] == 0) unassigned++;
            else if ((assign[v] == 1 && lit > 0) || (assign[v] == -1 && lit < 0)) {
                satisfied = 1; break;
            }
        }
        if (!satisfied && unassigned == 0) return 0; // 有空子句
        cl = cl->next;
    }
    // 检查是否所有子句都被满足
    cl = F->head;
    while (cl) {
        int satisfied = 0;
        for (int i = 0; i < cl->len; i++) {
            int lit = cl->literals[i];
            int v = abs(lit);
            if ((assign[v] == 1 && lit > 0) || (assign[v] == -1 && lit < 0)) {
                satisfied = 1; break;
            }
        }
        if (!satisfied) return 2; // 还有未满足的子句
        cl = cl->next;
    }
    return 1; // 全部满足
}

// DPLL递归
int DPLL(Formula *F, int *assign, int var_num) {
    unit_propagate(F, assign, var_num);
    int status = check_formula(F, assign);
    if (status == 1) return 1; // SAT
    if (status == 0) return 0; // UNSAT
    // 选择第一个未赋值变量分裂
    int v = 1;
    while (v <= var_num && assign[v] != 0) v++;
    if (v > var_num) return 0;
    // 试1
    int *assign1 = (int*)malloc((var_num+1)*sizeof(int));
    memcpy(assign1, assign, (var_num+1)*sizeof(int));
    assign1[v] = 1;
    if (DPLL(F, assign1, var_num)) {
        memcpy(assign, assign1, (var_num+1)*sizeof(int));
        free(assign1);
        return 1;
    }
    // 试-1
    int *assign2 = (int*)malloc((var_num+1)*sizeof(int));
    memcpy(assign2, assign, (var_num+1)*sizeof(int));
    assign2[v] = -1;
    int res = DPLL(F, assign2, var_num);
    if (res) memcpy(assign, assign2, (var_num+1)*sizeof(int));
    free(assign1); free(assign2);
    return res;
}

// ===== 主控与输入输出 =====
int main(int argc, char *argv[]) {
    if (argc < 2) { printf("用法: %s file.cnf\n", argv[0]); return 1; }
    Formula *F = parse_cnf(argv[1]);
    if (!F) return 1;
    printf("CNF解析结果：\n");
    print_formula(F);

    int *assign = (int*)calloc(F->var_num+1, sizeof(int));
    clock_t start = clock();
    int sat = DPLL(F, assign, F->var_num);
    clock_t end = clock();
    double t = (end - start) * 1000.0 / CLOCKS_PER_SEC;

    // 输出结果
    FILE *fp = fopen("result.res", "w");
    if (sat) {
        printf("SAT\n");
        fprintf(fp, "s 1\nv ");
        for (int i = 1; i <= F->var_num; i++)
            fprintf(fp, "%d ", assign[i] ? (assign[i] * i) : i);
        fprintf(fp, "\n");
    } else {
        printf("UNSAT\n");
        fprintf(fp, "s 0\n");
    }
    printf("t %.0f ms\n", t);
    fprintf(fp, "t %.0f\n", t);
    fclose(fp);
    free(assign);
    // 释放内存略
    return 0;
}