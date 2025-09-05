#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 数独参数
#define N 9
// 自然顺序编码：(i*81 + j*9 + k + 1)，i,j,k均从0开始
#define VAR(i,j,k) (i*81 + j*9 + k + 1)

// 生成百分号数独的CNF文件
void shuduToCnf(int grid[N][N],char* filename) {
    FILE* f = fopen(filename, "w");
    int count = 0;
    char clauses[120000][100]; 
    int idx = 0;

    // 1. 每个格子至少填一个数
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++) {
            int len = 0;
            for(int k=0;k<N;k++)
                len += sprintf(clauses[idx]+len, "%d ", VAR(i,j,k));
            len += sprintf(clauses[idx]+len, "0\n");
            idx++;
        }

    // 2. 每个格子至多填一个数
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            for(int k1=0;k1<N;k1++)
                for(int k2=k1+1;k2<N;k2++) {
                    sprintf(clauses[idx++], "-%d -%d 0\n", VAR(i,j,k1), VAR(i,j,k2));
                }

    // 3. 每行每个数字只出现一次
    for(int i=0;i<N;i++)
        for(int k=0;k<N;k++)
            for(int j1=0;j1<N;j1++)
                for(int j2=j1+1;j2<N;j2++) {
                    sprintf(clauses[idx++], "-%d -%d 0\n", VAR(i,j1,k), VAR(i,j2,k));
                }

    // 4. 每列每个数字只出现一次
    for(int j=0;j<N;j++)
        for(int k=0;k<N;k++)
            for(int i1=0;i1<N;i1++)
                for(int i2=i1+1;i2<N;i2++) {
                    sprintf(clauses[idx++], "-%d -%d 0\n", VAR(i1,j,k), VAR(i2,j,k));
                }

    // 5. 每宫每个数字只出现一次（标准3x3宫）
    for(int bi=0;bi<3;bi++)
        for(int bj=0;bj<3;bj++)
            for(int k=0;k<N;k++)
                for(int u=0;u<3;u++)
                    for(int v=0;v<3;v++)
                        for(int w=u*3+v+1;w<9;w++) {
                            int u2=w/3, v2=w%3;
                            if(u*3+v < w)
                                sprintf(clauses[idx++], "-%d -%d 0\n",
                                    VAR(bi*3+u, bj*3+v, k), VAR(bi*3+u2, bj*3+v2, k));
                        }

    // 6. 撇对角线约束（左上-右下）
    for(int k=0;k<N;k++) {
        for(int i1=0;i1<N;i1++)
            for(int i2=i1+1;i2<N;i2++) {
                // 主对角线: i==j
                sprintf(clauses[idx++], "-%d -%d 0\n", VAR(i1,i1,k), VAR(i2,i2,k));
            }
    }
    // 7. 撇对角线约束（右上-左下）
    for(int k=0;k<N;k++) {
        for(int i1=0;i1<N;i1++)
            for(int i2=i1+1;i2<N;i2++) {
                // 副对角线: i+j==N-1
                sprintf(clauses[idx++], "-%d -%d 0\n", VAR(i1,N-1-i1,k), VAR(i2,N-1-i2,k));
            }
    }

    // 8. 窗口约束（仅对指定2个九宫格窗口）
    int window_topleft[2][2] = { {2,2}, {6,6} }; // 左上角坐标(1-based)
    for(int w=0; w<2; w++) {
        int basei = window_topleft[w][0]-1; // 转为0-based
        int basej = window_topleft[w][1]-1;
        // 收集窗口内所有格子坐标
        int cells[9][2], cnt=0;
        for(int di=0; di<3; di++)
            for(int dj=0; dj<3; dj++) {
                int i = basei+di;
                int j = basej+dj;
                if(i<N && j<N) { // 防止越界
                    cells[cnt][0]=i;
                    cells[cnt][1]=j;
                    cnt++;
                }
            }
        // 对窗口内每个数字加唯一性约束
        for(int k=0; k<N; k++) {
            for(int a=0; a<cnt; a++)
                for(int b=a+1; b<cnt; b++)
                    sprintf(clauses[idx++], "-%d -%d 0\n",
                        VAR(cells[a][0], cells[a][1], k),
                        VAR(cells[b][0], cells[b][1], k));
        }
    }

    // 9. 已知格子
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(grid[i][j] > 0)
                sprintf(clauses[idx++], "%d 0\n", VAR(i,j,grid[i][j]-1));

    count = idx;

    // 写入文件头
    fprintf(f, "p cnf %d %d\n", N*N*N, count);
    // 写入所有子句
    for(int i=0;i<count;i++)
        fputs(clauses[i], f);

    fclose(f);
}

// 解析SAT解文件，输出数独
void analySat(char* filename, int grid[N][N]) {
    FILE* f = fopen(filename, "r");
    if(!f) { printf("无法打开结果文件\n"); return; }
    char line[1024];
    int found = 0;
    while(fgets(line, sizeof(line), f)) {
        if(line[0]=='v') {
            found = 1;
            char* p = line+1;
            int x;
            while(sscanf(p, "%d", &x)==1) {
                if(x>0) {
                    // 逆变换公式：x = i*81 + j*9 + k + 1
                    x--; // 先减去1，得到0-based编码
                    int i = x / 81;
                    int j = (x % 81) / 9;
                    int k = x % 9;
                    grid[i][j] = k + 1;
                }
                while(*p && *p!=' ') p++;
                while(*p==' ') p++;
            }
        }
    }
    fclose(f);
    if(!found) printf("未找到解！\n");
}

// 主程序
int main() {
    int grid[N][N];
    int temp=0;
    printf("请输入9x9数独题目（空格用0表示）：\n");
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++){
            scanf("%d",&temp);
            if(temp==46) temp=0;
            grid[i][j]=temp; 
        }
            

    shuduToCnf(grid, "sudoku.cnf");

    // 调用SAT求解器
    // 假设satpro.cpp已编译为satpro.exe，且支持命令行输入
    // system("satpro.exe < sudoku.cnf > sudoku.res");
    // 这里直接调用satpro.cpp的主函数也可以，但需适配接口
    printf("请手动运行satpro.exe，输入sudoku.cnf文件名，输出sudoku.res\n");
    printf("运行完毕后按回车继续...");
    getchar(); getchar();

    // 解析SAT解
    int ans[N][N] = {0};
    analySat("sudoku.res", ans);

    printf("数独解：\n");
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++)
            printf("%d ", ans[i][j]);
        printf("\n");
    }
    return 0;
}