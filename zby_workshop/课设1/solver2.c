#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solver.h"

// 判断子句状态
// 1: 已满足, 0: 已冲突, -1: 未定
static int clause_status(Clause* cl, int* assign) {
    int undecided = 0;
    for (int i = 0; i < cl->len; i++) {
        int lit = cl->literals[i];
        int v = abs(lit);
        int val = assign[v];
        if (val == 0) undecided = 1;
        else if ((lit > 0 && val == 1) || (lit < 0 && val == -1)) return 1;
    }
    return undecided ? -1 : 0;
}

// 单子句传播
static int unit_propagate(Formula* F, int* assign) {
    int changed;
    do {
        changed = 0;
        Clause* cl = F->head;
        while (cl) {
            int sat = 0, undecided = 0, last_lit = 0;
            for (int i = 0; i < cl->len; i++) {
                int lit = cl->literals[i];
                int v = abs(lit);
                int val = assign[v];
                if (val == 0) { undecided++; last_lit = lit; }
                else if ((lit > 0 && val == 1) || (lit < 0 && val == -1)) { sat = 1; break; }
            }
            if (!sat && undecided == 0) return 0; // 冲突
            if (!sat && undecided == 1) {
                int v = abs(last_lit);
                int want = (last_lit > 0 ? 1 : -1);
                if (assign[v] == 0) { assign[v] = want; changed = 1; }
                else if (assign[v] != want) return 0; // 冲突
            }
            cl = cl->next;
        }
    } while (changed);
    return 1;
}

// 纯文字消元
static void pure_literal_elim(Formula* F, int* assign, int var_num) {
    int* pos = (int*)calloc(var_num + 1, sizeof(int));
    int* neg = (int*)calloc(var_num + 1, sizeof(int));
    Clause* cl = F->head;
    while (cl) {
        for (int i = 0; i < cl->len; i++) {
            int lit = cl->literals[i];
            int v = abs(lit);
            if (assign[v] != 0) continue;
            if (lit > 0) pos[v] = 1;
            else neg[v] = 1;
        }
        cl = cl->next;
    }
    for (int v = 1; v <= var_num; v++) {
        if (assign[v] == 0) {
            if (pos[v] && !neg[v]) assign[v] = 1;
            else if (!pos[v] && neg[v]) assign[v] = -1;
        }
    }
    free(pos); free(neg);
}

// 检查公式
static int check_formula(Formula* F, int* assign) {
    Clause* cl = F->head;
    int undecided = 0;
    while (cl) {
        int st = clause_status(cl, assign);
        if (st == 0) return 0; // 冲突
        if (st == -1) undecided = 1;
        cl = cl->next;
    }
    return undecided ? -1 : 1;
}

// 变量选择：选择出现次数最多的未赋值变量
static int choose_variable(Formula* F, int* assign, int var_num) {
    int* count = (int*)calloc(var_num + 1, sizeof(int));
    Clause* cl = F->head;
    while (cl) {
        int st = clause_status(cl, assign);
        if (st == 1) { cl = cl->next; continue; }
        for (int i = 0; i < cl->len; i++) {
            int v = abs(cl->literals[i]);
            if (assign[v] == 0) count[v]++;
        }
        cl = cl->next;
    }
    int best = 0, best_count = -1;
    for (int v = 1; v <= var_num; v++) {
        if (assign[v] == 0 && count[v] > best_count) {
            best_count = count[v];
            best = v;
        }
    }
    free(count);
    if (best == 0) {
        for (int v = 1; v <= var_num; v++) if (assign[v] == 0) return v;
    }
    return best;
}

// 递归 DPLL
static int dpll_rec(Formula* F, int* assign, int var_num) {
    if (!unit_propagate(F, assign)) return 0;
    pure_literal_elim(F, assign, var_num);

    int chk = check_formula(F, assign);
    if (chk == 1) return 1;
    if (chk == 0) return 0;

    int v = choose_variable(F, assign, var_num);
    if (v == 0) return 0;

    int* tmp = (int*)malloc((var_num + 1) * sizeof(int));

    memcpy(tmp, assign, (var_num + 1) * sizeof(int));
    tmp[v] = 1;
    if (dpll_rec(F, tmp, var_num)) { memcpy(assign, tmp, (var_num + 1) * sizeof(int)); free(tmp); return 1; }

    memcpy(tmp, assign, (var_num + 1) * sizeof(int));
    tmp[v] = -1;
    if (dpll_rec(F, tmp, var_num)) { memcpy(assign, tmp, (var_num + 1) * sizeof(int)); free(tmp); return 1; }

    free(tmp);
    return 0;
}

// 主接口
int DPLL(Formula* F, int* assign, int var_num) {
    memset(assign, 0, (var_num + 1) * sizeof(int));
    return dpll_rec(F, assign, var_num);
}
