#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define N 9

// 检查数字在行中是否唯一
bool isUniqueInRow(int grid[N][N], int row, int num) {
    for (int col = 0; col < N; col++) {
        if (grid[row][col] == num) {
            return false;
        }
    }
    return true;
}

// 检查数字在列中是否唯一
bool isUniqueInCol(int grid[N][N], int col, int num) {
    for (int row = 0; row < N; row++) {
        if (grid[row][col] == num) {
            return false;
        }
    }
    return true;
}

// 检查数字在3x3宫中是否唯一
bool isUniqueInBox(int grid[N][N], int startRow, int startCol, int num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (grid[row + startRow][col + startCol] == num) {
                return false;
            }
        }
    }
    return true;
}

// 检查数字在撇对角线中是否唯一
bool isUniqueInSlashDiagonal(int grid[N][N], int num) {
    for (int i = 0; i < N; i++) {
        if (grid[i][N-1-i] == num) {
            return false;
        }
    }
    return true;
}

// 检查数字在额外窗口中是否唯一
bool isUniqueInExtraWindow(int grid[N][N], int windowRow, int windowCol, int num) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[windowRow + i][windowCol + j] == num) {
                return false;
            }
        }
    }
    return true;
}

// 检查数字是否可以安全放置
bool isSafe(int grid[N][N], int row, int col, int num) {
    return isUniqueInRow(grid, row, num) &&
           isUniqueInCol(grid, col, num) &&
           isUniqueInBox(grid, row - row % 3, col - col % 3, num) &&
           isUniqueInSlashDiagonal(grid, num) &&
           isUniqueInExtraWindow(grid, 0, 0, num) &&  // 左上额外窗口
           isUniqueInExtraWindow(grid, 6, 6, num);    // 右下额外窗口
}

// 生成完整的百分号数独终盘
bool generateFullSudoku(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                // 随机尝试数字1-9
                int nums[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                
                // 随机打乱数字顺序
                for (int i = 0; i < 9; i++) {
                    int j = rand() % 9;
                    int temp = nums[i];
                    nums[i] = nums[j];
                    nums[j] = temp;
                }
                
                for (int i = 0; i < 9; i++) {
                    int num = nums[i];
                    if (isSafe(grid, row, col, num)) {
                        grid[row][col] = num;
                        
                        if (generateFullSudoku(grid)) {
                            return true;
                        }
                        
                        grid[row][col] = 0; // 回溯
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// 挖洞法生成游戏格局
void digHoles(int grid[N][N], int holes) {
    int holesDug = 0;
    
    while (holesDug < holes) {
        int row = rand() % N;
        int col = rand() % N;
        
        // 如果这个位置已经有洞了，跳过
        if (grid[row][col] == 0) {
            continue;
        }
        
        // 保存原始值
        int original = grid[row][col];
        grid[row][col] = 0;
        
        // 检查挖洞后是否仍有唯一解（简化版检查）
        // 这里使用简单的检查：确保行、列、宫中该数字仍有唯一位置可填
        bool stillValid = true;
        
        // 检查行中是否还有其他位置可以填这个数字
        int rowCount = 0;
        for (int c = 0; c < N; c++) {
            if (grid[row][c] == 0 && isSafe(grid, row, c, original)) {
                rowCount++;
            }
        }
        if (rowCount == 0) {
            stillValid = false;
        }
        
        // 检查列中是否还有其他位置可以填这个数字
        int colCount = 0;
        for (int r = 0; r < N; r++) {
            if (grid[r][col] == 0 && isSafe(grid, r, col, original)) {
                colCount++;
            }
        }
        if (colCount == 0) {
            stillValid = false;
        }
        
        // 检查宫中是否还有其他位置可以填这个数字
        int boxRow = row - row % 3;
        int boxCol = col - col % 3;
        int boxCount = 0;
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                if (grid[boxRow + r][boxCol + c] == 0 && 
                    isSafe(grid, boxRow + r, boxCol + c, original)) {
                    boxCount++;
                }
            }
        }
        if (boxCount == 0) {
            stillValid = false;
        }
        
        if (!stillValid) {
            // 恢复原始值
            grid[row][col] = original;
        } else {
            holesDug++;
        }
    }
}

// 打印数独
void printSudoku(int grid[N][N]) {
    printf("+-------+-------+-------+\n");
    for (int i = 0; i < N; i++) {
        printf("| ");
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0) {
                printf(". ");
            } else {
                printf("%d ", grid[i][j]);
            }
            if ((j + 1) % 3 == 0) {
                printf("| ");
            }
        }
        printf("\n");
        if ((i + 1) % 3 == 0) {
            printf("+-------+-------+-------+\n");
        }
    }
}

// 生成百分号数独游戏格局
void generatePercentSudoku(int difficulty) {
    int grid[N][N] = {0};
    
    // 设置随机种子
    srand(time(NULL));
    
    printf("正在生成完整的百分号数独终盘...\n");
    if (generateFullSudoku(grid)) {
        printf("完整终盘生成成功！\n");
        printf("完整终盘：\n");
        printSudoku(grid);
        
        // 根据难度设置挖洞数量
        int holes;
        switch (difficulty) {
            case 1: holes = 30; break; // 简单
            case 2: holes = 40; break; // 中等
            case 3: holes = 50; break; // 困难
            default: holes = 40;
        }
        
        printf("\n正在挖洞生成游戏格局（挖洞数量：%d）...\n", holes);
        digHoles(grid, holes);
        
        printf("游戏格局生成成功！\n");
        printf("游戏格局：\n");
        printSudoku(grid);
        
        // 标记额外窗口位置
        printf("\n额外窗口位置：\n");
        printf("左上额外窗口（行0-2，列0-2）：\n");
        printf("右下额外窗口（行6-8，列6-8）：\n");
        printf("撇对角线位置：\n");
        for (int i = 0; i < N; i++) {
            printf("(%d,%d) ", i, N-1-i);
        }
        printf("\n");
        
    } else {
        printf("无法生成完整的百分号数独终盘！\n");
    }
}

int main() {
    int difficulty;
    
    printf("=== 百分号数独游戏生成器 ===\n");
    printf("请选择难度：\n");
    printf("1. 简单\n");
    printf("2. 中等\n");
    printf("3. 困难\n");
    printf("请输入选择（1-3）：");
    scanf("%d", &difficulty);
    
    if (difficulty < 1 || difficulty > 3) {
        printf("无效选择，使用中等难度\n");
        difficulty = 2;
    }
    
    generatePercentSudoku(difficulty);
    
    return 0;
}