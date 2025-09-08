#include <stdio.h>

#define N 9

// 变量编码
int var(int i, int j, int k) {
    return (i - 1) * 81 + (j - 1) * 9 + k;
}

// 输出单元格唯一性约束
void cell_constraints(FILE* fp) {
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++) {
            // 至少有一个数字
            for (int k = 1; k <= N; k++)
                fprintf(fp, "%d ", var(i, j, k));
            fprintf(fp, "0\n");
            // 不能有两个数字
            for (int k1 = 1; k1 <= N; k1++)
                for (int k2 = k1 + 1; k2 <= N; k2++)
                    fprintf(fp, "-%d -%d 0\n", var(i, j, k1), var(i, j, k2));
        }
}

// 行唯一性
void row_constraints(FILE* fp) {
    for (int i = 1; i <= N; i++)
        for (int k = 1; k <= N; k++)
            for (int j1 = 1; j1 <= N; j1++)
                for (int j2 = j1 + 1; j2 <= N; j2++)
                    fprintf(fp, "-%d -%d 0\n", var(i, j1, k), var(i, j2, k));
}

// 列唯一性
void col_constraints(FILE* fp) {
    for (int j = 1; j <= N; j++)
        for (int k = 1; k <= N; k++)
            for (int i1 = 1; i1 <= N; i1++)
                for (int i2 = i1 + 1; i2 <= N; i2++)
                    fprintf(fp, "-%d -%d 0\n", var(i1, j, k), var(i2, j, k));
}

// 宫唯一性
void box_constraints(FILE* fp) {
    for (int boxr = 0; boxr < 3; boxr++)
        for (int boxc = 0; boxc < 3; boxc++)
            for (int k = 1; k <= N; k++)
                for (int i1 = 0; i1 < 3; i1++)
                    for (int j1 = 0; j1 < 3; j1++)
                        for (int i2 = 0; i2 < 3; i2++)
                            for (int j2 = 0; j2 < 3; j2++) {
                                int r1 = boxr * 3 + i1 + 1, c1 = boxc * 3 + j1 + 1;
                                int r2 = boxr * 3 + i2 + 1, c2 = boxc * 3 + j2 + 1;
                                if (r1 < r2 || (r1 == r2 && c1 < c2))
                                    fprintf(fp, "-%d -%d 0\n", var(r1, c1, k), var(r2, c2, k));
                            }
}

// 副对角线唯一性（左下到右上）
void anti_diag_constraints(FILE* fp) {
    for (int k = 1; k <= N; k++)
        for (int i1 = 1; i1 <= N; i1++)
            for (int i2 = i1 + 1; i2 <= N; i2++) {
                int j1 = N + 1 - i1, j2 = N + 1 - i2;
                fprintf(fp, "-%d -%d 0\n", var(i1, j1, k), var(i2, j2, k));
            }
}

// 阴影窗口唯一性
void shadow_constraints(FILE* fp) {
    // 左上阴影窗口(行1~3,列1~3)
    for (int k = 1; k <= N; k++)
        for (int i1 = 1; i1 <= 3; i1++)
            for (int j1 = 1; j1 <= 3; j1++)
                for (int i2 = 1; i2 <= 3; i2++)
                    for (int j2 = 1; j2 <= 3; j2++)
                        if (i1 < i2 || (i1 == i2 && j1 < j2))
                            fprintf(fp, "-%d -%d 0\n", var(i1, j1, k), var(i2, j2, k));
    // 右下阴影窗口(行5~7,列5~7)
    for (int k = 1; k <= N; k++)
        for (int i1 = 5; i1 <= 7; i1++)
            for (int j1 = 5; j1 <= 7; j1++)
                for (int i2 = 5; i2 <= 7; i2++)
                    for (int j2 = 5; j2 <= 7; j2++)
                        if (i1 < i2 || (i1 == i2 && j1 < j2))
                            fprintf(fp, "-%d -%d 0\n", var(i1, j1, k), var(i2, j2, k));
}

// 输出已知格子（题面）约束
void clue_constraints(FILE* fp, int puzzle[N][N]) {
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            if (puzzle[i - 1][j - 1])
                fprintf(fp, "%d 0\n", var(i, j, puzzle[i - 1][j - 1]));
}

int main() {
    FILE* fp = fopen("percent_sudoku.cnf", "w");
    if (!fp) { printf("无法打开文件\n"); return 1; }

    // 题面（0表示空格，可自行修改）
    int puzzle[N][N] = { 0 };

    // 统计子句数
    int clauses = 0;
    // 这里只统计变量数，子句数可用脚本统计或先输出0再用工具修正
    int vars = N * N * N;
    fprintf(fp, "p cnf %d 0\n", vars); // 先写0，后续可用脚本修正

    // 约束输出
    cell_constraints(fp);
    row_constraints(fp);
    col_constraints(fp);
    box_constraints(fp);
    anti_diag_constraints(fp);
    shadow_constraints(fp);
    clue_constraints(fp, puzzle);

    fclose(fp);
    printf("已生成percent_sudoku.cnf\n");
    return 0;
}