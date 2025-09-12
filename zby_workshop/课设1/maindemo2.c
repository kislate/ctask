#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cnfparser.h"
#include "solver.h"

int main() {
    char filename[256];
    printf("请输入CNF文件路径：");
    scanf("%255s", filename);

    Formula *F = parse_cnf(filename);
    if (!F) return 1;
    printf("CNF解析结果：\n");
    print_formula(F);

    int *assign = (int*)calloc(F->var_num+1, sizeof(int));
    clock_t start = clock();
    int sat = DPLL(F, assign, F->var_num);
    clock_t end = clock();
    double t = (end - start) * 1000.0 / CLOCKS_PER_SEC;

    // 构造结果文件名（与算例同名，扩展名为.res）
    char resfile[256];
    strncpy(resfile, filename, sizeof(resfile));
    char *dot = strrchr(resfile, '.');
    if (dot) strcpy(dot, ".res");
    else strcat(resfile, ".res");

    FILE *fp = fopen(resfile, "w");
    if (!fp) { printf("无法写入结果文件！\n"); free(assign); free_formula(F); return 1; }

    // 输出结果到文件
    if (sat) {
        fprintf(fp, "s 1\nv ");
        for (int i = 1; i <= F->var_num; i++)
            fprintf(fp, "%d ", assign[i] == 1 ? i : -i);
        fprintf(fp, "\n");
    } else {
        fprintf(fp, "s 0\n");
    }
    fprintf(fp, "t %.0f\n", t);

    // 同时打印到屏幕
    if (sat) {
        printf("SAT\nv ");
        for (int i = 1; i <= F->var_num; i++)
            printf("%d ", assign[i] == 1 ? i : -i);
        printf("\n");
    } else {
        printf("UNSAT\n");
    }
    printf("t %.0f ms\n", t);

    fclose(fp);
    free(assign);
    free_formula(F);
    return 0;
}