#ifndef SUDOKU_H
#define SUDOKU_H

#define N 9

// 全局数独盘面
extern int grid[N][N];

// 生成完整的百分号数独解
void generate_full_sudoku();

// 挖洞生成题目（保证唯一解）
void dig_holes(int holes);

// 打印数独盘面
void print_grid();

// 将百分号数独题目转为 SAT 文件 (DIMACS CNF)
void sudoku_to_cnf(const char* filename);

#endif
