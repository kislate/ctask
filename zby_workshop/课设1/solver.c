#include <stdlib.h>
#include <string.h>
#include "solver.h"

// 单子句传播
static int unit_propagate(Formula* F, int* assign, int var_num) {
    int changed = 1;
    while (changed) {
        changed = 0;
        Clause* cl = F->head;
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
static int check_formula(Formula* F, int* assign) {
    Clause* cl = F->head;
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
int DPLL(Formula* F, int* assign, int var_num) {
    unit_propagate(F, assign, var_num);
    int status = check_formula(F, assign);
    if (status == 1) return 1; // SAT
    if (status == 0) return 0; // UNSAT
    int v = 1;
    while (v <= var_num && assign[v] != 0) v++;
    if (v > var_num) return 0;
    int* assign1 = (int*)malloc((var_num + 1) * sizeof(int));
    memcpy(assign1, assign, (var_num + 1) * sizeof(int));
    assign1[v] = 1;
    if (DPLL(F, assign1, var_num)) {
        memcpy(assign, assign1, (var_num + 1) * sizeof(int));
        free(assign1);
        return 1;
    }
    int* assign2 = (int*)malloc((var_num + 1) * sizeof(int));
    memcpy(assign2, assign, (var_num + 1) * sizeof(int));
    assign2[v] = -1;
    int res = DPLL(F, assign2, var_num);
    if (res) memcpy(assign, assign2, (var_num + 1) * sizeof(int));
    free(assign1); free(assign2);
    return res;
}