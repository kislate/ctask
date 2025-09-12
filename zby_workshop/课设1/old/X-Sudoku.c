#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 9

int grid[N][N];

// 判断是否在左上阴影窗口（以(2,2)为中心的3x3格，即行1~3,列1~3）
int in_left_shadow(int row, int col) {
    return row >= 1 && row <= 3 && col >= 1 && col <= 3;
}

// 判断是否在右下阴影窗口（以(6,6)为中心的3x3格，即行5~7,列5~7）
int in_right_shadow(int row, int col) {
    return row >= 5 && row <= 7 && col >= 5 && col <= 7;
}

// 判断当前位置填val是否合法
int is_valid(int row, int col, int val) {
    for (int i = 0; i < N; i++)
        if (grid[row][i] == val || grid[i][col] == val)
            return 0;
    int box_r = row / 3 * 3, box_c = col / 3 * 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[box_r + i][box_c + j] == val)
                return 0;
    // 副对角线（左下到右上）
    if (row + col == N - 1) {
        for (int i = 0; i < N; i++)
            if (grid[i][N - 1 - i] == val)
                return 0;
    }
    // 左上阴影窗口
    if (in_left_shadow(row, col)) {
        for (int i = 1; i <= 3; i++)
            for (int j = 1; j <= 3; j++)
                if (grid[i][j] == val)
                    return 0;
    }
    // 右下阴影窗口
    if (in_right_shadow(row, col)) {
        for (int i = 5; i <= 7; i++)
            for (int j = 5; j <= 7; j++)
                if (grid[i][j] == val)
                    return 0;
    }
    return 1;
}

// 随机打乱1~9
void shuffle(int* a, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int t = a[i]; a[i] = a[j]; a[j] = t;
    }
}

// 递归填充完整数独
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

// 解的计数器，用于唯一解判定
int solution_count = 0;
void solve(int pos) {
    if (pos == N * N) {
        solution_count++;
        return;
    }
    int row = pos / N, col = pos % N;
    if (grid[row][col]) {
        solve(pos + 1);
        return;
    }
    for (int v = 1; v <= 9; v++) {
        if (is_valid(row, col, v)) {
            grid[row][col] = v;
            solve(pos + 1);
            grid[row][col] = 0;
            if (solution_count > 1) return; // 剪枝
        }
    }
}

// 挖洞法
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
            grid[r][c] = backup; // 恢复
        }
        else {
            attempts--;
        }
    }
}

// 打印数独
void print_grid() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", grid[i][j]);
        printf("\n");
    }
}

// ========== SAT转化部分 ==========
int var(int i, int j, int k) {
    return (i - 1) * N * N + (j - 1) * N + k;
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
                int j1 = N + 1 - i1, j2 = N + 1 - i2;
                fprintf(fp, "-%d -%d 0\n", var(i1, j1, k), var(i2, j2, k));
                (*clause_count)++;
            }
}

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

void clue_constraints(FILE* fp, int* clause_count) {
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            if (grid[i - 1][j - 1]) {
                fprintf(fp, "%d 0\n", var(i, j, grid[i - 1][j - 1]));
                (*clause_count)++;
            }
}

void transform_to_cnf() {
    int clause_count = 0;
    FILE* fp = fopen("sudoku.cnf", "w");
    if (!fp) { printf("无法打开文件！\n"); return; }

    int vars = N * N * N;
    fprintf(fp, "p cnf %d 0\n", vars);

    cell_constraints(fp, &clause_count);
    row_constraints(fp, &clause_count);
    col_constraints(fp, &clause_count);
    box_constraints(fp, &clause_count);
    anti_diag_constraints(fp, &clause_count);
    left_shadow_constraints(fp, &clause_count);
    right_shadow_constraints(fp, &clause_count);
    clue_constraints(fp, &clause_count);

    fseek(fp, 7, SEEK_SET);
    fprintf(fp, "%d\n", clause_count);

    fclose(fp);
    printf("已生成百分号数独SAT问题文件：sudoku.cnf\n");
}

// ========== 菜单 ==========
void menu() {
    int choice;
    int holes;
    srand((unsigned)time(0));
    while (1) {
        printf("\n==== 百分号数独系统 ====\n");
        printf("1. 生成完整百分号数独\n");
        printf("2. 挖空出题（唯一解）\n");
        printf("3. 转化为CNF文件\n");
        printf("0. 退出\n");
        printf("请选择：");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
            case 1:
                memset(grid, 0, sizeof(grid));
                fill(0);
                printf("完整解：\n");
                print_grid();
                break;
            case 2:
                printf("请输入挖空数量：");
                if (scanf("%d", &holes) != 1) break;
                dig_holes(holes);
                printf("题目：\n");
                print_grid();
                break;
            case 3:
                transform_to_cnf();
                break;
            case 0:
                return;
            default:
                printf("无效选项！\n");
        }
    }
}

int main() {
    menu();
    return 0;
}