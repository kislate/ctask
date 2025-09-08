#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sudoku.h"

int grid[N][N];  // 全局数独盘面

// 判断是否在左上阴影窗口
static int in_left_shadow(int row, int col) {
    return row >= 1 && row <= 3 && col >= 1 && col <= 3;
}
// 判断是否在右下阴影窗口
static int in_right_shadow(int row, int col) {
    return row >= 5 && row <= 7 && col >= 5 && col <= 7;
}

// 判断合法性
static int is_valid(int row, int col, int val) {
    for (int i = 0; i < N; i++)
        if (grid[row][i] == val || grid[i][col] == val) return 0;
    int box_r = row / 3 * 3, box_c = col / 3 * 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[box_r + i][box_c + j] == val) return 0;
    if (row + col == N - 1) {
        for (int i = 0; i < N; i++)
            if (grid[i][N - 1 - i] == val) return 0;
    }
    if (in_left_shadow(row + 1, col + 1)) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (grid[i][j] == val) return 0;
    }
    if (in_right_shadow(row + 1, col + 1)) {
        for (int i = 5; i <= 7; i++)
            for (int j = 5; j <= 7; j++)
                if (grid[i][j] == val) return 0;
    }
    return 1;
}

// 打乱数组
static void shuffle(int* a, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int t = a[i]; a[i] = a[j]; a[j] = t;
    }
}

// 填充完整解
static int fill(int pos) {
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

void generate_full_sudoku() {
    srand((unsigned)time(0));
    memset(grid, 0, sizeof(grid));
    fill(0);
}

// --- 解计数（保证唯一解） ---
static int solution_count;
static void solve_count(int pos) {
    if (pos == N * N) { solution_count++; return; }
    int row = pos / N, col = pos % N;
    if (grid[row][col]) { solve_count(pos + 1); return; }
    for (int v = 1; v <= 9; v++) {
        if (is_valid(row, col, v)) {
            grid[row][col] = v;
            solve_count(pos + 1);
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
        solve_count(0);
        if (solution_count != 1) {
            grid[r][c] = backup;
        } else {
            attempts--;
        }
    }
}

// 打印
void print_grid() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", grid[i][j]);
        printf("\n");
    }
}

// ================= CNF 转换 =================
static int var(int i, int j, int k) {
    return (i - 1) * N * N + (j - 1) * N + k;
}

void sudoku_to_cnf(const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) { printf("无法写文件！\n"); return; }

    int vars = N * N * N;
    fprintf(fp, "p cnf %d XXXXX\n", vars);
    int clause_count = 0;

    // --- 单元格唯一性 ---
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= N; k++) fprintf(fp, "%d ", var(i,j,k));
            fprintf(fp, "0\n"); clause_count++;
            for (int k1 = 1; k1 <= N; k1++)
                for (int k2 = k1+1; k2 <= N; k2++) {
                    fprintf(fp, "-%d -%d 0\n", var(i,j,k1), var(i,j,k2));
                    clause_count++;
                }
        }

    // --- 行唯一性 ---
    for (int i = 1; i <= N; i++)
        for (int k = 1; k <= N; k++)
            for (int j1 = 1; j1 <= N; j1++)
                for (int j2 = j1+1; j2 <= N; j2++) {
                    fprintf(fp, "-%d -%d 0\n", var(i,j1,k), var(i,j2,k));
                    clause_count++;
                }

    // --- 列唯一性 ---
    for (int j = 1; j <= N; j++)
        for (int k = 1; k <= N; k++)
            for (int i1 = 1; i1 <= N; i1++)
                for (int i2 = i1+1; i2 <= N; i2++) {
                    fprintf(fp, "-%d -%d 0\n", var(i1,j,k), var(i2,j,k));
                    clause_count++;
                }

    // --- 宫唯一性 ---
    for (int br = 0; br < 3; br++)
        for (int bc = 0; bc < 3; bc++)
            for (int k = 1; k <= N; k++)
                for (int i1 = 0; i1 < 3; i1++)
                    for (int j1 = 0; j1 < 3; j1++)
                        for (int i2 = 0; i2 < 3; i2++)
                            for (int j2 = 0; j2 < 3; j2++) {
                                int r1 = br*3+i1+1, c1 = bc*3+j1+1;
                                int r2 = br*3+i2+1, c2 = bc*3+j2+1;
                                if (r1 < r2 || (r1==r2 && c1<c2)) {
                                    fprintf(fp,"-%d -%d 0\n", var(r1,c1,k), var(r2,c2,k));
                                    clause_count++;
                                }
                            }

    // --- 副对角线 ---
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) fprintf(fp,"%d ", var(i,N+1-i,k));
        fprintf(fp,"0\n"); clause_count++;
        for (int i1=1;i1<=N;i1++)
            for (int i2=i1+1;i2<=N;i2++) {
                fprintf(fp,"-%d -%d 0\n", var(i1,N+1-i1,k), var(i2,N+1-i2,k));
                clause_count++;
            }
    }

    // --- 左上阴影 ---
    for (int k=1;k<=N;k++) {
        for (int i=2;i<=4;i++) for (int j=2;j<=4;j++) fprintf(fp,"%d ", var(i,j,k));
        fprintf(fp,"0\n"); clause_count++;
        for (int i1=2;i1<=4;i1++) for (int j1=2;j1<=4;j1++)
            for (int i2=2;i2<=4;i2++) for (int j2=2;j2<=4;j2++)
                if (i1<i2 || (i1==i2 && j1<j2)) {
                    fprintf(fp,"-%d -%d 0\n", var(i1,j1,k), var(i2,j2,k));
                    clause_count++;
                }
    }

    // --- 右下阴影 ---
    for (int k=1;k<=N;k++) {
        for (int i=6;i<=8;i++) for (int j=6;j<=8;j++) fprintf(fp,"%d ", var(i,j,k));
        fprintf(fp,"0\n"); clause_count++;
        for (int i1=6;i1<=8;i1++) for (int j1=6;j1<=8;j1++)
            for (int i2=6;i2<=8;i2++) for (int j2=6;j2<=8;j2++)
                if (i1<i2 || (i1==i2 && j1<j2)) {
                    fprintf(fp,"-%d -%d 0\n", var(i1,j1,k), var(i2,j2,k));
                    clause_count++;
                }
    }


    // --- 题面 ---
    for (int i=1;i<=N;i++)
        for (int j=1;j<=N;j++)
            if (grid[i-1][j-1]) {
                fprintf(fp,"%d 0\n", var(i,j,grid[i-1][j-1]));
                clause_count++;
            }

    rewind(fp);
    fprintf(fp, "p cnf %d %d\n", vars, clause_count);
    fclose(fp);
}
