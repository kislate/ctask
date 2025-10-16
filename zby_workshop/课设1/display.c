#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "solver.h"
#include "cnfparser.h"
#include "sudoku.h"

Formula* current_formula = NULL;//SAT公式缓存
char current_filename[256];//CNF文件路径缓存，用于存放.res文件

//SAT求解器菜单
void sat_menu() {
    int choice;
    while (1) {
        printf("\n===== SAT 求解器 =====\n");
        printf("1. 读取 CNF 文件\n");
        printf("2. 打印 CNF 文件\n");
        printf("3. 求解 CNF 文件\n");
        printf("0. 返回主菜单\n");
        printf("请选择: ");
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            return;
        case 1:
            printf("请输入 CNF 文件路径: ");
            scanf("%s", current_filename);
            if (current_formula) free_formula(current_formula);
            current_formula = parse_cnf(current_filename);
            if (current_formula) printf("文件读取成功！\n");
            else printf("读取失败！\n");
            break;
        case 2:
            if (!current_formula) printf("请先读取 CNF 文件！\n");
            else print_formula(current_formula);
            break;
        case 3:
            if (!current_formula) {
                printf("请先读取 CNF 文件！\n");
            }
            else {
                int* assign = (int*)calloc(current_formula->var_num + 1, sizeof(int));
                clock_t start = clock();
                int sat = DPLL(current_formula, assign, current_formula->var_num);
                clock_t end = clock();
                double t = (end - start) * 1000.0 / CLOCKS_PER_SEC;

                //屏幕打印
                printf("结果: %s\n", sat ? "SAT" : "UNSAT");
                if (sat) {
                    printf("赋值: ");
                    for (int i = 1; i <= current_formula->var_num; i++)
                        printf("%d ", assign[i] == 1 ? i : -i);
                    printf("\n");
                }
                printf("t %.0f ms\n", t);

                //构造.res文件名
                char resfile[300];
                strncpy(resfile, current_filename, sizeof(resfile));
                char* dot = strrchr(resfile, '.');
                if (dot) strcpy(dot, ".res");
                else strcat(resfile, ".res");

                FILE* fp = fopen(resfile, "w");
                if (!fp) {
                    printf("无法写入结果文件！\n");
                }
                else {
                    if (sat) {
                        fprintf(fp, "s 1\nv ");
                        for (int i = 1; i <= current_formula->var_num; i++)
                            fprintf(fp, "%d ", assign[i] == 1 ? i : -i);
                        fprintf(fp, "\n");
                    }
                    else {
                        fprintf(fp, "s 0\n");
                    }
                    fprintf(fp, "t %.0f\n", t);
                    fclose(fp);
                    printf("结果已保存到 %s\n", resfile);
                }
                free(assign);
            }
            break;

        default:
            printf("无效输入！\n");
        }
    }
}

//数独游戏菜单
void sudoku_menu() {
    int choice;
	int holes = 40;//可设定挖洞数量
    while (1) {
        printf("\n===== 数独游戏 =====\n");
        printf("1. 生成完整百分号数独\n");
        printf("2. 生成百分号数独问题\n");
        printf("3. 使用 DPLL 求解问题\n");
        printf("0. 返回主菜单\n");
        printf("请选择: ");
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            return;
        case 1:
            generate_full_sudoku();
            printf("完整解：\n");
            print_grid();
            break;
        case 2:
            generate_full_sudoku();
            dig_holes(holes);
            printf("题目：\n");
            print_grid();

            sudoku_to_cnf("sudoku.cnf");
            printf("已生成 sudoku.cnf，可用选项3进行求解。\n");
            break;
        case 3:
            printf("开始读取 sudoku.cnf 并调用 SAT 求解器...\n");
            if (current_formula) free_formula(current_formula);
            current_formula = parse_cnf("sudoku.cnf");
            if (!current_formula) {
                printf("解析 sudoku.cnf 失败！请先用选项2生成题目。\n");
                break;
            }
            int* assign = (int*)calloc(current_formula->var_num + 1, sizeof(int));
            clock_t start = clock();
            int sat = DPLL(current_formula, assign, current_formula->var_num);
            clock_t end = clock();
            double t = (end - start) * 1000.0 / CLOCKS_PER_SEC;
            //屏幕打印
            printf("结果: %s\n", sat ? "SAT" : "UNSAT");
            printf("t %.0f ms\n", t);
            //保存.res文件
            FILE* fp = fopen("sudoku.res", "w");
            if (!fp) {
                printf("无法写入结果文件！\n");
            }
            else {
                if (sat) {
                    fprintf(fp, "s 1\nv ");
                    for (int i = 1; i <= current_formula->var_num; i++)
                        fprintf(fp, "%d ", assign[i] == 1 ? i : -i);
                    fprintf(fp, "\n");
                }
                else {
                    fprintf(fp, "s 0\n");
                }
                fprintf(fp, "t %.0f\n", t);
                fclose(fp);
                printf("结果已保存到 sudoku.res\n");
            }
            //解读并打印数独解
            if (sat) {
                int solved[N][N];
                if (load_solution_from_res("sudoku.res", solved)) {
                    printf("解出的数独：\n");
                    for (int i = 0; i < N; i++) {
                        for (int j = 0; j < N; j++)
                            printf("%d ", solved[i][j]);
                        printf("\n");
                    }
                }
            }
            free(assign);
            break;

        default:
            printf("无效输入！\n");
        }
    }
}

//主菜单
int main() {
    int choice;
    while (1) {
        printf("\n===== 主菜单 =====\n");
        printf("1. SAT 求解器\n");
        printf("2. 数独游戏\n");
        printf("0. 退出\n");
        printf("请选择: ");
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            if (current_formula) free_formula(current_formula);
            return 0;
        case 1:
            sat_menu();
            break;
        case 2:
            sudoku_menu();
            break;
        default:
            printf("无效输入！\n");
        }
    }
}

+-------------------+      +-------------------+      +-------------------+
|      Formula      | ---> |      Clause 1     | ---> |      Clause 2     | ---> ...
|-------------------|      |-------------------|      |-------------------|
| head ------------+-----> | literals[]        |      | literals[]        |
| var_num          |      | len               |      | len               |
| clause_num       |      | next ------------ |      | next              |
+-------------------+      +-------------------+      +-------------------+

assign[] <--- 变量编号与Formula中的变量一一对应

grid[9][9] <--- 数独棋盘，可转化为Formula