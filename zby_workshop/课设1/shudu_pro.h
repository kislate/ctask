#ifndef SUDOKU_H
#define SUDOKU_H

#define N 9

extern int grid[N][N];

// 数独生成与操作
void generate_full_sudoku();
void dig_holes(int holes);
void print_grid();

// CNF 转换
void sudoku_to_cnf(const char* filename);

// 从 .res 文件读解并还原数独盘面
int load_solution_from_res(const char* filename, int solved_grid[N][N]);

#endif
