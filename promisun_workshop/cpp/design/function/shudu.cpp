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