#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <windows.h>

//////基于DPLL算法的SAT求解器---->优化可以对DPLL升级变为可以学习的CDCL算法



        //define区
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define literalincrement 50


        //结构定义区
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


        //子函数声明区
int readCNFFile(CNF &cnf);
CNF* createCNF(int varcount,int clausecount);
answer* createAnswer(int varcount);
void releaseCNF(CNF *cnf);
int printAnswerToFile(answer *ans, char *filename,int time);
void releaseAns(answer *ans);
int isClauseOk(clause* cl,answer* ans);
int isUClause(clause* cl,answer* ans);
int UintSpread(CNF *cnf,answer *ans);
int dpll(CNF *cnf,answer *ans);

//主函数
int main()
{
    SetConsoleOutputCP(65001);
    clock_t start, end;
    double milliseconds;
    
    CNF cnf;

    //初始化CNF结构体
    cnf.varcount = 0;
    cnf.clausecount = 0;
    cnf.clauses = NULL;

    //读取CNF文件
    if(readCNFFile(cnf) == ERROR) {
        printf("读取CNF文件失败\n");
        return ERROR;
    }
    printf("CNF文件读取成功\n");
    answer *ans = createAnswer(cnf.varcount);
   
    // 记录开始时间
    start = clock();
    
    //调用DPLL算法求解
    if(dpll(&cnf, ans)) {
        printf("SAT\n");
        ans->assignments[0] = 1; //标记为满足
    } else {
        printf("UNSAT\n");
        ans->assignments[0] = 0; //标记为不满足
    }
    // 记录结束时间
    end = clock();
    
    //打印结果

    for(int i=1;i<=cnf.varcount;i++){
        if(ans->assignments[i] != 0) { //只输出已赋值的变量
            printf("%d ", ans->assignments[i] > 0 ? i : -i);
        }
    }
    printf("\n");
    milliseconds = ((double)(end - start) * 1000) / CLOCKS_PER_SEC;
    printf("运行时间: %.2f 毫秒\n", milliseconds);

    releaseCNF(&cnf);
    releaseAns(ans);
    return 0;
}


//子函数模块
        //1.读取CNF文件
int readCNFFile(CNF &cnf) {

    int min_clause_length = 100;
    int uint=0;//直接读取数据时来波简单的预处理                       //////////////此后在此处可以优化一点点

    char filename[100];
    printf("请输入CNF文件名: ");
    scanf("%s", filename);
    FILE *file = fopen(filename, "r");
    if(!file){
        printf("无法打开文件%s\n",filename);
        return ERROR;
    }
    while(1){
        char c = fgetc(file);
        if(c==EOF) break;
        if(c=='c'){ //注释行
            while(c!='\n' && c!=EOF) c = fgetc(file);
            continue;
        }
        if(c=='p'){
            fscanf(file," cnf %d %d",&cnf.varcount,&cnf.clausecount);
            cnf.clauses = (clause *)malloc(cnf.clausecount * sizeof(clause));
        }
        for(int i=0;i<cnf.clausecount;i++){
            clause *cl= (clause *)malloc(sizeof(clause));
            cl->literalcount = 0;
            cl->literals = (int *)malloc(50 * sizeof(int));
            while(1){   
                if(cl->literalcount>=sizeof(cl->literals)/sizeof(int)){ //如果文字数超过了数组大小，扩容
                    cl->literals = (int *)realloc(cl->literals, (cl->literalcount + literalincrement) * sizeof(int));
                }
                int literal;
                fscanf(file, "%d", &literal);
                if(literal == 0) break; //子句结束
                cl->literals[cl->literalcount++] = literal; //存储文字
            }
            
            cnf.clauses[i] = *cl; //存储子句内容
            free(cl); //释放临时分配的clause指针
        }
    }
    fclose(file);
    return OK; 
}
 
        //2.创建CNF结构体
CNF* createCNF(int varcount,int clausecount){
    CNF *cnf = (CNF *)malloc(sizeof(CNF));
    cnf->varcount = varcount;
    cnf->clausecount = clausecount;
    cnf->clauses = (clause *)malloc(clausecount * sizeof(clause));
    return cnf;
}

        //3.创建解
answer* createAnswer(int varcount){
    answer *ans=(answer *)malloc(sizeof(answer));
    ans->varcount = varcount;
    ans->assignments = (int *)calloc(varcount+1 , sizeof(int));//第一个元素存储求解结果,其他元素存储变量赋值从1开始
    return ans;
}

        //4.释放CNF结构体内存
void releaseCNF(CNF *cnf){
    for(int i=0;i<cnf->clausecount;i++){
        free(cnf->clauses[i].literals);//先释放子句的文字数组
    }
    free(cnf->clauses); //再释放子句数组
    free(cnf); //最后释放CNF结构体本身
}

        //5.打印最终结果解（以文件形式输出）
        // 输出文件规范：
        // 对每个算例的求解结果要求输出到一个与算例同名的文件（文件扩展名为.res），文件内容与格式要求如下：
        // s求解结果//1表示满足，0表示不满足，-1表示在限定时间内未完成求解
        // v -1 2 -3 … //满足时，每个变元的赋值序列，-1表示第一个变元1取假，2表示第二个变元取真，用空格分开，此处为示例。
        // t 17     //以毫秒为单位的DPLL执行时间，可增加分支规则执行次数信息
int printAnswerToFile(answer *ans, char *filename,double time){
    FILE *file=fopen(filename,"w");
    if(!file){
        return ERROR;
    }
    fprintf(file, "s %d\n", ans->assignments[0]); 
    fprintf(file, "v ");
    for(int i=1;i<=ans->varcount;i++){
        if(ans->assignments[i] != 0) { //只输出已赋值的变量
            fprintf(file, "%d ", ans->assignments[i] > 0 ? i : -i);
        }
    }
    fprintf(file, "\nt %.2f 毫秒\n",time); 
    fclose(file);
}

        //6.释放答案结构体内存
void releaseAns(answer *ans){
    free(ans->assignments); 
    free(ans); 
}

//////创建createClause、销毁destroyClause、增加addClause、删除removeClause、判断是否为单子句isUnitClause、评估子句的真假状态evaluateClause
        
        //7.评估子句状态
int isClauseOk(clause* cl,answer* ans){
    int a=0;
    for(int i=0;i<cl->literalcount;i++){
        int lit = cl->literals[i];
        if((lit > 0 && ans->assignments[lit] == 0) || (lit < 0 && ans->assignments[-lit] == 0)) a=1; 
        if(lit > 0 && ans->assignments[lit] == 1) return 1; 
        if(lit < 0 && ans->assignments[-lit] == -1) return 1; 
    }
    if(a) return 0; //子句未定
    return -1;
}

        //8.判断单子句
int isUClause(clause* cl,answer* ans){
    int unsignedcount=0,code=0;
    for(int i=0;i<cl->literalcount;i++){
        int lit = cl->literals[i];
        if((lit > 0 && ans->assignments[lit] == 0) || (lit < 0 && ans->assignments[-lit] == 0)) 
        {
            unsignedcount++;
            code=lit;
        } 
    }
    if(unsignedcount==1) return abs(code);
    else return FALSE;
}

//////DPLL算法核心模块
        //9.DPLL算法主体
int UintSpread(CNF *cnf,answer *ans){
    int state=0;
    do{
        state=0;
        for(int i=0;i<cnf->clausecount;i++){
            clause *cl=&cnf->clauses[i];
            
            if(isClauseOk(cl,ans)==1) continue;
            if(isClauseOk(cl,ans)==-1) return FALSE; 

            int var = isUClause(cl,ans);
            if(var) { 
                        ans->assignments[var] = 1;
                        state=1;
                        break;
                    }
            }
    }while (state); //存在单子句就继续传播
    return TRUE;    
}

int dpll(CNF *cnf,answer *ans){
    
    if (!UintSpread(cnf, ans)) {
        return FALSE; 
    }
    
    // 检查是否所有子句都已满足
    int allsat=1;
    for(int i=0;i<cnf->clausecount;i++){
        clause *cl=&cnf->clauses[i];
        if(isClauseOk(cl,ans)==0) {allsat=0;break;}
        if(isClauseOk(cl,ans)==-1) return FALSE; 
    }
    if(allsat==1){
        ans->assignments[0] = 1; //标记为满足
        return TRUE; 
    }

    // 选择未赋值的变量
    int var = 0;
    for (int i = 1; i <= cnf->varcount; i++) {
        if (ans->assignments[i] == 0) {
            var = i;
            break;
        }
    }
    
    // 尝试赋值为真
    answer* anscopy = createAnswer(cnf->varcount);
    memcpy(anscopy->assignments, ans->assignments, (cnf->varcount + 1) * sizeof(int));
    anscopy->assignments[var] = 1;
    if (dpll(cnf, anscopy)) {
        memcpy(ans->assignments, anscopy->assignments, (cnf->varcount + 1) * sizeof(int));
        free(anscopy);
        return TRUE;
    }
    free(anscopy);

    // 尝试赋值为假
    anscopy = createAnswer(cnf->varcount);
    memcpy(anscopy->assignments, ans->assignments, (cnf->varcount + 1) * sizeof(int));
    anscopy->assignments[var] = -1;
    if (dpll(cnf, anscopy)) {
        memcpy(ans->assignments, anscopy->assignments, (cnf->varcount + 1) * sizeof(int));
        free(anscopy);
        return TRUE;
    }
    free(anscopy);
    return FALSE;
}
