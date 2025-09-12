#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 9
#define MAXVARS 1000
#define MAXCLAUSES 100000

// ========== create_sudoku 部分 ==========
int grid[N][N];

int in_left_shadow(int row, int col) { return row >= 1 && row <= 3 && col >= 1 && col <= 3; }
int in_right_shadow(int row, int col) { return row >= 5 && row <= 7 && col >= 5 && col <= 7; }
int is_valid(int row, int col, int val) {
    for (int i = 0; i < N; i++)
        if (grid[row][i] == val || grid[i][col] == val)
            return 0;
    int box_r = row / 3 * 3, box_c = col / 3 * 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[box_r + i][box_c + j] == val)
                return 0;
    if (row + col == N - 1) {
        for (int i = 0; i < N; i++)
            if (grid[i][N - 1 - i] == val)
                return 0;
    }
    if (in_left_shadow(row, col)) {
        for (int i = 1; i <= 3; i++)
            for (int j = 1; j <= 3; j++)
                if (grid[i][j] == val)
                    return 0;
    }
    if (in_right_shadow(row, col)) {
        for (int i = 5; i <= 7; i++)
            for (int j = 5; j <= 7; j++)
                if (grid[i][j] == val)
                    return 0;
    }
    return 1;
}
void shuffle(int* a, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int t = a[i]; a[i] = a[j]; a[j] = t;
    }
}
int fill(int pos) {
    if (pos == N * N) return 1;
    int row = pos / N, col = pos % N;
    int nums[N];
    for (int i = 0; i < N; i++) nums[i] = i + 1;
    shuffle(nums, N);
    for (int i = 0; i < N; i++) {
        if (is_valid(row, col, nums[i])) {
            grid[row][col] = nums[i];
            if (fill(pos + 1)) return 1;
            grid[row][col] = 0;
        }
    }
    return 0;
}
int solution_count = 0;
void solve(int pos) {
    if (pos == N * N) { solution_count++; return; }
    int row = pos / N, col = pos % N;
    if (grid[row][col]) { solve(pos + 1); return; }
    for (int v = 1; v <= 9; v++) {
        if (is_valid(row, col, v)) {
            grid[row][col] = v;
            solve(pos + 1);
            grid[row][col] = 0;
            if (solution_count > 1) return;
        }
    }
}
void dig_holes(int holes) {
    int attempts = holes;
    while (attempts > 0) {
        int r = rand() % N, c = rand() % N;
        if (grid[r][c] == 0) continue;
        int backup = grid[r][c];
        grid[r][c] = 0;
        solution_count = 0;
        solve(0);
        if (solution_count != 1) {
            grid[r][c] = backup;
        }
        else {
            attempts--;
        }
    }
}
void print_grid(int g[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", g[i][j]);
        printf("\n");
    }
}

// ========== transform 部分 ==========
int var(int i, int j, int k) {
    return (i - 1) * 81 + (j - 1) * 9 + k;
}
void cell_constraints(FILE* fp, int* clause_count) {
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= N; k++)
                fprintf(fp, "%d ", var(i, j, k));
            fprintf(fp, "0\n");
            (*clause_count)++;
            for (int k1 = 1; k1 <= N; k1++)
                for (int k2 = k1 + 1; k2 <= N; k2++) {
                    fprintf(fp, "-%d -%d 0\n", var(i, j, k1), var(i, j, k2));
                    (*clause_count)++;
                }
        }
}
void row_constraints(FILE* fp, int* clause_count) {
    for (int i = 1; i <= N; i++)
        for (int k = 1; k <= N; k++)
            for (int j1 = 1; j1 <= N; j1++)
                for (int j2 = j1 + 1; j2 <= N; j2++) {
                    fprintf(fp, "-%d -%d 0\n", var(i, j1, k), var(i, j2, k));
                    (*clause_count)++;
                }
}
void col_constraints(FILE* fp, int* clause_count) {
    for (int j = 1; j <= N; j++)
        for (int k = 1; k <= N; k++)
            for (int i1 = 1; i1 <= N; i1++)
                for (int i2 = i1 + 1; i2 <= N; i2++) {
                    fprintf(fp, "-%d -%d 0\n", var(i1, j, k), var(i2, j, k));
                    (*clause_count)++;
                }
}
void box_constraints(FILE* fp, int* clause_count) {
    for (int boxr = 0; boxr < 3; boxr++)
        for (int boxc = 0; boxc < 3; boxc++)
            for (int k = 1; k <= N; k++)
                for (int i1 = 0; i1 < 3; i1++)
                    for (int j1 = 0; j1 < 3; j1++)
                        for (int i2 = 0; i2 < 3; i2++)
                            for (int j2 = 0; j2 < 3; j2++) {
                                int r1 = boxr * 3 + i1 + 1, c1 = boxc * 3 + j1 + 1;
                                int r2 = boxr * 3 + i2 + 1, c2 = boxc * 3 + j2 + 1;
                                if (r1 < r2 || (r1 == r2 && c1 < c2)) {
                                    fprintf(fp, "-%d -%d 0\n", var(r1, c1, k), var(r2, c2, k));
                                    (*clause_count)++;
                                }
                            }
}
void anti_diag_constraints(FILE* fp, int* clause_count) {
    for (int k = 1; k <= N; k++)
        for (int i1 = 1; i1 <= N; i1++)
            for (int i2 = i1 + 1; i2 <= N; i2++) {
                fprintf(fp, "-%d -%d 0\n", var(i1, N - i1, k), var(i2, N - i2, k));
                (*clause_count)++;
            }
}

void sudoku_to_cnf() {
    FILE* fp = fopen("sudoku.cnf", "w");
    int clause_count = 0;

    // 写文件头
    fprintf(fp, "p cnf %d %d\n", N * N * N, 4 * N * N * N);  // 变量数和子句数

    // 数独约束
    cell_constraints(fp, &clause_count);
    row_constraints(fp, &clause_count);
    col_constraints(fp, &clause_count);
    box_constraints(fp, &clause_count);
    anti_diag_constraints(fp, &clause_count);

    fclose(fp);
}

// ========== SAT Solver 部分 ==========
typedef struct {
    int* lits;  // 存储子句中的字面量
    int len;    // 子句的长度
} Clause;

typedef struct {
    Clause clauses[MAXCLAUSES];  // 子句数组
    int clause_num;              // 子句的数量
    int var_num;                 // 变量的数量
} Formula;

int absint(int x) {
    return x > 0 ? x : -x;
}

int parse_cnf(const char* filename, Formula* F) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("无法打开文件\n");
        return 0;
    }

    char line[4096];
    F->clause_num = 0;
    F->var_num = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (line[0] == 'c') continue;  // 跳过注释行
        if (line[0] == 'p') {  // 读取文件头
            sscanf(line, "p cnf %d %d", &F->var_num, &F->clause_num);
            continue;
        }

        int lits[1000], cnt = 0, x;
        char* p = line;
        while (sscanf(p, "%d", &x) == 1 && x != 0) {  // 读取子句的字面量
            lits[cnt++] = x;
            while (*p && *p != ' ') p++;
            while (*p == ' ') p++;
        }

        if (cnt > 0) {
            F->clauses[F->clause_num].lits = (int*)malloc(cnt * sizeof(int));
            memcpy(F->clauses[F->clause_num].lits, lits, cnt * sizeof(int));
            F->clauses[F->clause_num].len = cnt;
            F->clause_num++;
        }
    }

    fclose(fp);
    return 1;
}

// 单元传播
int unit_propagate(Formula* F, int* assign, int var_num) {
    int changed = 1;
    while (changed) {
        changed = 0;
        for (int ci = 0; ci < F->clause_num; ci++) {
            Clause* cl = &F->clauses[ci];
            int unassigned = 0, last_lit = 0, satisfied = 0;
            for (int i = 0; i < cl->len; i++) {
                int lit = cl->lits[i];
                int v = absint(lit);
                if (assign[v] == 0) {
                    unassigned++;
                    last_lit = lit;
                }
                else if ((assign[v] == 1 && lit > 0) || (assign[v] == -1 && lit < 0)) {
                    satisfied = 1;
                    break;
                }
            }

            // 如果子句未满足且只剩一个未赋值的字面量，则进行单元传播
            if (!satisfied && unassigned == 1) {
                int v = absint(last_lit);
                assign[v] = last_lit > 0 ? 1 : -1;
                changed = 1;
            }
        }
    }
    return 1;
}

// 检查公式是否满足
int check_formula(Formula* F, int* assign) {
    for (int ci = 0; ci < F->clause_num; ci++) {
        Clause* cl = &F->clauses[ci];
        int satisfied = 0, unassigned = 0;
        for (int i = 0; i < cl->len; i++) {
            int lit = cl->lits[i];
            int v = absint(lit);
            if (assign[v] == 0) unassigned++;
            else if ((assign[v] == 1 && lit > 0) || (assign[v] == -1 && lit < 0)) {
                satisfied = 1;
                break;
            }
        }
        if (!satisfied && unassigned == 0) return 0;  // 存在空子句
    }

    // 检查是否所有子句都满足
    for (int ci = 0; ci < F->clause_num; ci++) {
        Clause* cl = &F->clauses[ci];
        int satisfied = 0;
        for (int i = 0; i < cl->len; i++) {
            int lit = cl->lits[i];
            int v = absint(lit);
            if ((assign[v] == 1 && lit > 0) || (assign[v] == -1 && lit < 0)) {
                satisfied = 1;
                break;
            }
        }
        if (!satisfied) return 2;  // 还有未满足的子句
    }

    return 1;  // 所有子句都满足
}

// DPLL算法求解
int DPLL(Formula* F, int* assign, int var_num) {
    unit_propagate(F, assign, var_num);
    int status = check_formula(F, assign);
    if (status == 1) return 1;  // SAT
    if (status == 0) return 0;  // UNSAT

    int v = 1;
    while (v <= var_num && assign[v] != 0) v++;
    if (v > var_num) return 0;  // 没有未赋值的变量

    // 尝试赋值为 1
    int* assign1 = (int*)malloc((var_num + 1) * sizeof(int));
    memcpy(assign1, assign, (var_num + 1) * sizeof(int));
    assign1[v] = 1;
    if (DPLL(F, assign1, var_num)) {
        memcpy(assign, assign1, (var_num + 1) * sizeof(int));
        free(assign1);
        return 1;
    }

    // 尝试赋值为 -1
    int* assign2 = (int*)malloc((var_num + 1) * sizeof(int));
    memcpy(assign2, assign, (var_num + 1) * sizeof(int));
    assign2[v] = -1;
    int res = DPLL(F, assign2, var_num);
    if (res) memcpy(assign, assign2, (var_num + 1) * sizeof(int));

    free(assign1);
    free(assign2);
    return res;
}

// 释放公式内存
void free_formula(Formula* F) {
    for (int i = 0; i < F->clause_num; i++) {
        free(F->clauses[i].lits);
    }
}

// 打印SAT解
void show_sat_solution(int* assign) {
    int sudoku[N][N] = { 0 };
    for (int v = 1; v <= N * N * N; v++) {
        if (assign[v] == 1) {
            int i = (v - 1) / 81 + 1;
            int j = ((v - 1) % 81) / 9 + 1;
            int k = ((v - 1) % 9) + 1;
            sudoku[i - 1][j - 1] = k;
        }
    }
    printf("SAT解如下：\n");
    print_grid(sudoku);
}


// ========== main 部分 ==========
void menu() {
    int choice;
    while (1) {
        printf("\n----- 数独生成器 -----\n");
        printf("1. 生成数独\n");
        printf("2. 挖空生成题目\n");
        printf("3. 使用SAT求解器求解\n");
        printf("4. 退出\n");
        printf("请输入选择：");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            memset(grid, 0, sizeof(grid));
            srand(time(NULL));
            fill(0);  // 生成完整的数独
            printf("生成的数独：\n");
            print_grid(grid);
            break;
        case 2:
            printf("输入挖空数量：");
            int holes;
            scanf("%d", &holes);
            dig_holes(holes);  // 挖空
            printf("生成的数独题目：\n");
            print_grid(grid);
            break;
        case 3:
            sudoku_to_cnf();  // 转换为CNF格式
            printf("已生成CNF文件。你可以将其输入到SAT求解器。\n");
            break;
        case 4:
            exit(0);
        default:
            printf("无效的选择，请重新输入。\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
