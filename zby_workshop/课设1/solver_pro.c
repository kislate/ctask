#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "solver.h"

//单子句传播
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

//纯文字消元
static int pure_literal_assign(Formula* F, int* assign, int var_num) {
    int changed = 1;
    while (changed) {
        changed = 0;
        int* seen = (int*)calloc(var_num + 1, sizeof(int));
        for (Clause* cl = F->head; cl; cl = cl->next) {
            for (int i = 0; i < cl->len; i++) {
                int lit = cl->literals[i];
                int v = abs(lit);
                if (assign[v] == 0) {
                    if (seen[v] == 0) seen[v] = (lit > 0 ? 1 : -1);
                    else if ((seen[v] == 1 && lit < 0) || (seen[v] == -1 && lit > 0)) {
                        seen[v] = 2; //同时出现正负->非纯文字
                    }
                }
            }
        }
        for (int v = 1; v <= var_num; v++) {
            if (assign[v] == 0 && (seen[v] == 1 || seen[v] == -1)) {
                assign[v] = seen[v]; //赋值纯文字
                changed = 1;
            }
        }
        free(seen);
    }
    return 1;
}

//检查公式
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
        if (!satisfied && unassigned == 0) return 0; //有空子句->UNSAT
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
    return 1; //全部满足->SAT
}

//JW启发式
static int choose_variable(Formula* F, int* assign, int var_num) {
    double* score = (double*)calloc(var_num + 1, sizeof(double));
    Clause* cl = F->head;

    while (cl) {
        int unassigned = 0;
        for (int i = 0; i < cl->len; i++) {
            int v = abs(cl->literals[i]);
            if (assign[v] == 0) unassigned++;
        }
        if (unassigned > 0) {
            double weight = pow(2.0, -unassigned);
            for (int i = 0; i < cl->len; i++) {
                int lit = cl->literals[i];
                int v = abs(lit);
                if (assign[v] == 0) {
                    score[v] += weight;
                }
            }
        }
        cl = cl->next;
    }

    int best_v = 0;
    double best_score = -1.0;
    for (int v = 1; v <= var_num; v++) {
        if (assign[v] == 0 && score[v] > best_score) {
            best_score = score[v];
            best_v = v;
        }
    }
    free(score);
    return best_v ? best_v : 1;
}

//DPLL主递归
int DPLL(Formula* F, int* assign, int var_num) {
    unit_propagate(F, assign, var_num);
    pure_literal_assign(F, assign, var_num);

    int status = check_formula(F, assign);
    if (status == 1) return 1;
    if (status == 0) return 0;

    int v = choose_variable(F, assign, var_num);

    //尝试v=true
    int* assign1 = (int*)malloc((var_num + 1) * sizeof(int));
    memcpy(assign1, assign, (var_num + 1) * sizeof(int));
    assign1[v] = 1;
    if (DPLL(F, assign1, var_num)) {
        memcpy(assign, assign1, (var_num + 1) * sizeof(int));
        free(assign1);
        return 1;
    }
    free(assign1);

    //尝试v=false
    int* assign2 = (int*)malloc((var_num + 1) * sizeof(int));
    memcpy(assign2, assign, (var_num + 1) * sizeof(int));
    assign2[v] = -1;
    int res = DPLL(F, assign2, var_num);
    if (res) memcpy(assign, assign2, (var_num + 1) * sizeof(int));
    free(assign2);

    return res;
}