#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    // 行、列
    for (int i = 0; i < N; i++)
        if (grid[row][i] == val || grid[i][col] == val)
            return 0;
    // 3x3宫
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

int main() {
    srand((unsigned)time(0));
    // 1. 生成完整解
    fill(0);
    printf("完整解：\n");
    print_grid();
    // 2. 挖洞
    int holes = 40; // 挖40个洞
    dig_holes(holes);
    printf("\n题目：\n");
    print_grid();
    return 0;
}