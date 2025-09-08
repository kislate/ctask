#include <stdio.h>
#include <stdlib.h>

#define N 9

extern int grid[N][N]; // 假设你的题面已在grid数组中

// 变量编码
int var(int i, int j, int k) {
    return (i - 1) * N * N + (j - 1) * N + k;
}

// 写入单元格唯一性约束
void cell_constraints(FILE* fp, int* clause_count) {
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++) {
            // 至少有一个数字
            for (int k = 1; k <= N; k++)
                fprintf(fp, "%d ", var(i, j, k));
            fprintf(fp, "0\n");
            (*clause_count)++;
            // 不能有两个数字
            for (int k1 = 1; k1 <= N; k1++)
                for (int k2 = k1 + 1; k2 <= N; k2++) {
                    fprintf(fp, "-%d -%d 0\n", var(i, j, k1), var(i, j, k2));
                    (*clause_count)++;
                }
        }
}

// 行唯一性
void row_constraints(FILE* fp, int* clause_count) {
    for (int i = 1; i <= N; i++)
        for (int k = 1; k <= N; k++)
            for (int j1 = 1; j1 <= N; j1++)
                for (int j2 = j1 + 1; j2 <= N; j2++) {
                    fprintf(fp, "-%d -%d 0\n", var(i, j1, k), var(i, j2, k));
                    (*clause_count)++;
                }
}

// 列唯一性
void col_constraints(FILE* fp, int* clause_count) {
    for (int j = 1; j <= N; j++)
        for (int k = 1; k <= N; k++)
            for (int i1 = 1; i1 <= N; i1++)
                for (int i2 = i1 + 1; i2 <= N; i2++) {
                    fprintf(fp, "-%d -%d 0\n", var(i1, j, k), var(i2, j, k));
                    (*clause_count)++;
                }
}

// 宫唯一性
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

// 副对角线唯一性（百分号数独）
void anti_diag_constraints(FILE* fp, int* clause_count) {
    for (int k = 1; k <= N; k++)
        for (int i1 = 1; i1 <= N; i1++)
            for (int i2 = i1 + 1; i2 <= N; i2++) {
                int j1 = N + 1 - i1, j2 = N + 1 - i2;
                fprintf(fp, "-%d -%d 0\n", var(i1, j1, k), var(i2, j2, k));
                (*clause_count)++;
            }
}

// 左上阴影窗口唯一性
void left_shadow_constraints(FILE* fp, int* clause_count) {
    for (int k = 1; k <= N; k++)
        for (int i1 = 1; i1 <= 3; i1++)
            for (int j1 = 1; j1 <= 3; j1++)
                for (int i2 = 1; i2 <= 3; i2++)
                    for (int j2 = 1; j2 <= 3; j2++)
                        if (i1 < i2 || (i1 == i2 && j1 < j2)) {
                            fprintf(fp, "-%d -%d 0\n", var(i1, j1, k), var(i2, j2, k));
                            (*clause_count)++;
                        }
}

// 右下阴影窗口唯一性
void right_shadow_constraints(FILE* fp, int* clause_count) {
    for (int k = 1; k <= N; k++)
        for (int i1 = 5; i1 <= 7; i1++)
            for (int j1 = 5; j1 <= 7; j1++)
                for (int i2 = 5; i2 <= 7; i2++)
                    for (int j2 = 5; j2 <= 7; j2++)
                        if (i1 < i2 || (i1 == i2 && j1 < j2)) {
                            fprintf(fp, "-%d -%d 0\n", var(i1, j1, k), var(i2, j2, k));
                            (*clause_count)++;
                        }
}

// 题面约束
void clue_constraints(FILE* fp, int* clause_count) {
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            if (grid[i - 1][j - 1]) {
                fprintf(fp, "%d 0\n", var(i, j, grid[i - 1][j - 1]));
                (*clause_count)++;
            }
}

int main() {
    int clause_count = 0;
    FILE* fp = fopen("sudoku.cnf", "w");
    if (!fp) { printf("无法打开文件！\n"); return 1; }

    // 变量数
    int vars = N * N * N;
    // 先写头部，子句数后面再覆盖
    fprintf(fp, "p cnf %d 0\n", vars);

    cell_constraints(fp, &clause_count);
    row_constraints(fp, &clause_count);
    col_constraints(fp, &clause_count);
    box_constraints(fp, &clause_count);
    anti_diag_constraints(fp, &clause_count);
    left_shadow_constraints(fp, &clause_count);
    right_shadow_constraints(fp, &clause_count);
    clue_constraints(fp, &clause_count);

    // 回写子句数
    fseek(fp, 7, SEEK_SET);
    fprintf(fp, "%d\n", clause_count);

    fclose(fp);
    printf("已生成百分号数独SAT问题文件：sudoku.cnf\n");
    return 0;
}