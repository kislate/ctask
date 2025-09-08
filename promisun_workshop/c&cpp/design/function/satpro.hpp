#ifndef SATPRO_H
#define SATPRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <windows.h>

        //define区
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define literalincrement 50

        //sat相关结构定义区
typedef struct{
    int *literals; //存储文字的数组
    int literalcount; //文字数
}clause;

typedef struct{
    clause *clauses; //存储子句的数组
    int varcount; //变量数
    int clausecount;//子句数
} CNF; 

typedef struct{
    int *assignments;//储存变量赋值的数组 (0=未赋值, 1=真, -1=假)
    int varcount; //变量数
}answer; //答案结构体

typedef struct vars {
    int var;           
    struct vars* next; 
} vars;

        //sat相关函数声明区
int readCNFFile(CNF &cnf,int** count,char* filename);
CNF* createCNF(int varcount,int clausecount);
answer* createAnswer(int varcount);
void releaseCNF(CNF *cnf);
int printAnswerToFile(answer *ans, char *filename,int time);
void releaseAns(answer *ans);
int isClauseOk(clause* cl,answer* ans);
int isUClause(clause* cl,answer* ans);
int UintSpread(CNF *cnf,answer *ans);
int dpll(CNF *cnf,answer *ans,vars* find);
vars *sortVar(int* count,int varcount);

// 数独相关声明
#define N 9
#define VAR(i,j,k) (i*81 + j*9 + k + 1)
void shuduToCnf(int grid[N][N], char* filename);
void analySat(char* filename, int grid[N][N]);

#endif