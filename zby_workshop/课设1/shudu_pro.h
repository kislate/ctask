#ifndef SUDOKU_H
#define SUDOKU_H

#define N 9

extern int grid[N][N];//全局二维数组grid，表示数独盘面

//数独生成
void generate_full_sudoku();

//挖空生成问题
void dig_holes(int holes);

//打印数独
void print_grid();

//CNF转换
void sudoku_to_cnf(const char* filename);

//从.res文件读解并还原数独
int load_solution_from_res(const char* filename, int solved_grid[N][N]);

#endif
