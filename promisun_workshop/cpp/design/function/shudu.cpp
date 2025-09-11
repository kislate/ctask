#include "satpro.hpp"

// 数独参数
#define N 9
// 自然顺序编码：(i*81 + j*9 + k + 1)，i,j,k均从0开始
#define VAR(i,j,k) ((i)*81 + (j)*9 + (k) + 1)

//生成百分号数独的CNF文件
void shuduToCnf(int grid[N][N],char* filename) {
    int count = 0;
    // 统计子句数
    // 0. 已知格子
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(grid[i][j] > 0) count++;
    // 1. 每个格子至少填一个数
    count += N*N;
    // 2. 每个格子至多填一个数
    count += N*N*N*(N-1)/2;
    // 3. 每行每个数字只出现一次
    count += N*N*N*(N-1)/2;
    // 4. 每列每个数字只出现一次
    count += N*N*N*(N-1)/2;
    // 5. 每宫每个数字只出现一次
    count += 9*N*36;
    // 6. 撇对角线约束（右上-左下）
    count += N*N*(N-1)/2;
    // 7. 窗口约束
    count += 2*N*36;


    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("无法打开文件 %s\n", filename);
        return;
    }
    // 写文件头
    fprintf(f, "p cnf %d %d\n", N*N*N, count);
    // 0. 已知格子
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(grid[i][j] > 0) {
                fprintf(f, "%d 0\n", VAR(i,j,grid[i][j]-1));
            }
    // 1. 每个格子至少填一个数
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++) {
            for(int k=0;k<N;k++)
                fprintf(f, "%d ", VAR(i,j,k));
            fprintf(f, "0\n");
        }
    // 2. 每个格子至多填一个数
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            for(int k1=0;k1<N;k1++)
                for(int k2=k1+1;k2<N;k2++) {
                    fprintf(f, "-%d -%d 0\n", VAR(i,j,k1), VAR(i,j,k2));
                }
    // 3. 每行每个数字只出现一次
    for(int i=0;i<N;i++)
        for(int k=0;k<N;k++)
            for(int j1=0;j1<N;j1++)
                for(int j2=j1+1;j2<N;j2++) {
                    fprintf(f, "-%d -%d 0\n", VAR(i,j1,k), VAR(i,j2,k));
                }
    // 4. 每列每个数字只出现一次
    for(int j=0;j<N;j++)
        for(int k=0;k<N;k++)
            for(int i1=0;i1<N;i1++)
                for(int i2=i1+1;i2<N;i2++) {
                    fprintf(f, "-%d -%d 0\n", VAR(i1,j,k), VAR(i2,j,k));
                }
    // // 有问题。。。 --->估计也是宏定义惹得祸  
    //5. 每宫每个数字只出现一次（标准3x3宫）
    for(int bi=0;bi<3;bi++)
        for(int bj=0;bj<3;bj++)
            for(int k=0;k<N;k++)
                for(int u=0;u<3;u++)
                    for(int v=0;v<3;v++)
                        for(int w=u*3+v+1;w<9;w++) {
                            int u2=w/3, v2=w%3;
                            if(u*3+v < w) {
                                fprintf(f, "-%d -%d 0\n",
                                    VAR(bi*3+u, bj*3+v, k), VAR(bi*3+u2, bj*3+v2, k));
                            }
                        }


    // 6. 撇对角线约束（右上-左下）???????第一行应该是-73 -138而非-9 -81         c.cnf 8872   --------->折磨我半天的宏定义，恶心死了，VAR(i1,N-1-i1,k)实为i1*81+N-1-i1*9+k+1,宏定义为直接替换故应在宏定义时加括号
    for(int k=0;k<N;k++) {
        for(int i1=0;i1<N;i1++)
            for(int i2=i1+1;i2<N;i2++) {
                fprintf(f, "-%d -%d 0\n", VAR(i1,N-1-i1,k), VAR(i2,N-1-i2,k));
                // printf("%d %d %d %d %d %d %d 0\n", i1,N-1-i1,i2,N-1-i2,k,VAR(i1,N-1-i1,k), VAR(i2,N-1-i2,k));
                // printf("%d %d 0\n", VAR(0,8,0), VAR(1,7,0));
            }
    }
    //单独没问题，组放在一起就有问题了？？？？？？？？？？？---->count计算不对导致的


    // 7. 窗口约束（仅对指定2个九宫格窗口）
    int window_topleft[2][2] = { {1,1}, {5,5} };  // 正确位置
    for(int w=0; w<2; w++) {
        int basei = window_topleft[w][0];  // 0-base
        int basej = window_topleft[w][1];  // 0-base
        int cells[9][2], cnt=0;
        
        for(int di=0; di<3; di++)
            for(int dj=0; dj<3; dj++) {
                int i = basei+di;
                int j = basej+dj;
                if(i < N && j < N) {
                    cells[cnt][0] = i;
                    cells[cnt][1] = j;
                    cnt++;
                }
            }
        
        for(int k=0; k<N; k++) {
            for(int a=0; a<cnt; a++)
                for(int b=a+1; b<cnt; b++) {
                    fprintf(f, "-%d -%d 0\n",
                        VAR(cells[a][0], cells[a][1], k),
                        VAR(cells[b][0], cells[b][1], k));
                }
        }
    }
    
    fclose(f);
    }


//解析SAT解文件，输出数独
int analySat(char* filename, int grid[N][N]) {
    FILE* f = fopen(filename, "r");
    if(!f) { printf("无法打开结果文件\n"); return -1; }
    char ch;
    int x;
    fscanf(f, "%c %d", &ch, &x);
    if(ch == 's'&& x==0) { fclose(f); return 0; }
    while(fscanf(f, "%c", &ch)==1){
        if(ch == 'v') break;
    } 
    while(fscanf(f, " %d", &x)==1 ){
        if(x > 0) {
                x--;
                int i = x / 81;
                int j = (x % 81) / 9;
                int k = x % 9;
                grid[i][j] = k+1 ;
            }
        ch=fgetc(f);
        if (ch == '\n' || ch == EOF) {
            ungetc(ch, f);  // 推回字符以便后续处理
            break;
        } 
        ungetc(ch, f);
    } 
    fclose(f);
    return 1;
}

//调试代码
// int main() {

//     char shuduname[100];
//     int grid[N][N];
//     printf("请输入要生成的cnf文件名:\n");
//     scanf("%s",shuduname);
//     printf("请输入9x9数独（每行9个字符，空格用'.'表示）：\n");
//     for (int i = 0; i < 9; i++) {
//         char line[16];
//         scanf("%15s", line);
//         for (int j = 0; j < 9; j++) {
//             if (line[j] == '.') grid[i][j] = 0;
//             else grid[i][j] = line[j] - '0';
//         }
//     }
//     printf("CNF文件%s生成完毕。\n", shuduname);
//     shuduToCnf(grid, shuduname);
//     printf("程序结束。\n");
//     return 0;
// }


//数独生成相关代码
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

// 检查数字在对角线中是否唯一
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
    int exrta1=1;
    int extra2=1;
    if(row>=1 && row<=3 && col>=1 && col<=3) exrta1=isUniqueInExtraWindow(grid, 1, 1, num);
    if(row>=5 && row<=7 && col>=5 && col<=7) exrta1=isUniqueInExtraWindow(grid, 5, 5, num);
    if(row+col==N-1) extra2=isUniqueInSlashDiagonal(grid, num);
    return isUniqueInRow(grid, row, num) &&
           isUniqueInCol(grid, col, num) &&
           isUniqueInBox(grid, row - row % 3, col - col % 3, num) &&
           exrta1 && extra2;  
}

// 生成完整的百分号数独
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
    
    //printf("正在生成完整的百分号数独终盘...\n");
    if (generateFullSudoku(grid)) {
        // printf("完整终盘生成成功！\n");
        // printf("完整终盘：\n");
        // printSudoku(grid);
        
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
        printf("\n");
        shuduToCnf(grid, "shudu.cnf");
    } 
    //else {
    //    printf("无法生成完整的百分号数独终盘！\n");
    //}
}

// int main() {
//     SetConsoleOutputCP(65001);
//     int difficulty;
    
//     printf("=== 百分号数独游戏生成器 ===\n");
//     printf("请选择难度：\n");
//     printf("1. 简单\n");
//     printf("2. 中等\n");
//     printf("3. 困难\n");
//     printf("请输入选择（1-3）：");
//     scanf("%d", &difficulty);
    
//     if (difficulty < 1 || difficulty > 3) {
//         printf("无效选择，使用中等难度\n");
//         difficulty = 2;
//     }
    
//     generatePercentSudoku(difficulty);
    
//     return 0;
// } 