#include "satpro.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>


int main() {
    SetConsoleOutputCP(65001);
    while (1) {
        printf("====================\n");
        printf("请选择功能：\n");
        printf("1. DPLL求解CNF文件\n");
        printf("2. 数独转CNF并求解\n");
        printf("0. 退出\n");
        printf("====================\n");
        printf("输入选项: ");
        int opt;
        scanf("%d", &opt);
        getchar(); // 吃掉回车
        if (opt == 0) break;
        if (opt == 1) {
            // DPLL求解CNF文件
            char cnfFile[256];
            CNF cnf;
            int* count = NULL;
            if (readCNFFile(cnf, &count, cnfFile) != OK) {
                printf("读取CNF文件失败！\n");
                continue;
            }
            answer* ans = createAnswer(cnf.varcount);
            vars* find = sortVar(count, cnf.varcount);
            int t1 = clock();
            int sat = dpll(&cnf, ans, find);
            int t2 = clock();
            ans->assignments[0] = sat ? 1 : 0;
            char resFile[256];
            strcpy(resFile, cnfFile);
            int i=0;
            for(;resFile[i]!='.';i++);
            resFile[i+1]='r'; resFile[i+2]='e'; resFile[i+3]='s'; resFile[i+4]='\0';
            if (printAnswerToFile(ans, resFile, t2-t1) == OK) {
                printf("结果已保存到: %s\n", resFile);
            } else {
                printf("结果文件保存失败！\n");
            }
            // 验证
            printf("是否验证结果？(1-verify.exe, 2-verify5000.exe, 0-跳过): ");
            int vopt; scanf("%d", &vopt); getchar();
            if (vopt == 1) {
                char cmd[512];
                snprintf(cmd, sizeof(cmd), "verify.exe %s %s", cnfFile, resFile);
                system(cmd);
            } else if (vopt == 2) {
                char cmd[512];
                snprintf(cmd, sizeof(cmd), "verify5000.exe %s %s", cnfFile, resFile);
                system(cmd);
            }
            releaseCNF(&cnf);
            releaseAns(ans);
            free(count);
            vars* p = find;
            while (p) { vars* q = p; p = p->next; free(q); }
        } else if (opt == 2) {
            // 数独转CNF并求解
            int grid[9][9];
            printf("请输入9x9数独（每行9个字符，空格用'.'表示）：\n");
            for (int i = 0; i < 9; i++) {
                char line[16];
                scanf("%15s", line);
                for (int j = 0; j < 9; j++) {
                    if (line[j] == '.') grid[i][j] = 0;
                    else grid[i][j] = line[j] - '0';
                }
            }
            char cnfFile[256];
            printf("请输入要保存的CNF文件名: ");
            scanf("%255s", cnfFile);
            shuduToCnf(grid, cnfFile);
            CNF cnf;
            int* count = NULL;
            if (readCNFFile(cnf, &count, cnfFile) != OK) {
                printf("读取CNF文件失败！\n");
                continue;
            }
            answer* ans = createAnswer(cnf.varcount);
            vars* find = sortVar(count, cnf.varcount);
            int t1 = clock();
            int sat = dpll(&cnf, ans, find);
            int t2 = clock();
            ans->assignments[0] = sat ? 1 : 0;
            char resFile[256];
            snprintf(resFile, sizeof(resFile), "%s.res", cnfFile);
            if (printAnswerToFile(ans, resFile, t2-t1) == OK) {
                printf("结果已保存到: %s\n", resFile);
            } else {
                printf("结果文件保存失败！\n");
            }
            // 解析并输出数独
            if (sat) {
                analySat(resFile, grid);
                printf("数独解如下：\n");
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9; j++) {
                        printf("%d ", grid[i][j]);
                    }
                    printf("\n");
                }
            } else {
                printf("无解！\n");
            }
            releaseCNF(&cnf);
            releaseAns(ans);
            free(count);
            vars* p = find;
            while (p) { vars* q = p; p = p->next; free(q); }
        } else {
            printf("无效选项！\n");
        }
    }
    printf("程序结束。\n");
    return 0;
}

//cnf文件要验证得第二行不空
//我的数独编码或解码文件可能出错了
