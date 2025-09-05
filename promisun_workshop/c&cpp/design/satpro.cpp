#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <windows.h>

//////基于DPLL算法的SAT求解器---->优化可以对DPLL升级变为可以学习的CDCL算法

//改进：
//1.选取变元策略

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

typedef struct vars {
    int var;           
    struct vars* next; 
} vars;

        //子函数声明区
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


//主函数
int main()
{
    SetConsoleOutputCP(65001);
    clock_t start, end;
    int milliseconds;
    
    CNF cnf;
    int* count;
    char filename[100];

    //初始化CNF结构体
    cnf.varcount = 0;
    cnf.clausecount = 0;
    cnf.clauses = NULL;
    count = NULL;

    //读取CNF文件
    if(readCNFFile(cnf,&count,filename) == ERROR) {
        printf("读取CNF文件失败\n");
        return ERROR;
    }
    printf("CNF文件读取成功\n");
    answer *ans = createAnswer(cnf.varcount);
    int i=0;
    for(;filename[i]!='.';i++);
    filename[i+1]='r';filename[i+2]='e';filename[i+3]='s';filename[i+4]='\0';


    // 记录开始时间
    start = clock();
    
    //变元活跃度排序（利用count数组创建链表）
    vars* find=sortVar(count,cnf.varcount);
    find=find->next;

    //调用DPLL算法求解
    if(dpll(&cnf, ans,find)) {
        printf("SAT\n");
        ans->assignments[0] = 1; //标记为满足
    } else {
        printf("UNSAT\n");
        ans->assignments[0] = 0; //标记为不满足
    }
    // 记录结束时间
    end = clock();
    
    //释放find链表
    vars* p=find;
    while(p){
        vars* temp=p;
        p=p->next;
        free(temp);
    }

    //打印结果
if(ans->assignments[0]==1){
    for(int i=1;i<=cnf.varcount;i++){
        if(ans->assignments[i] != 0) { 
            printf("%2d ", ans->assignments[i] > 0 ? i : -i);
        }
        else {
            printf("%d ", i);
        }
    }
}
    printf("\n");
    milliseconds = (int)(((double)(end - start) * 1000) / CLOCKS_PER_SEC);
    printf("运行时间: %d 毫秒\n", milliseconds);
        //打印至文件
    printAnswerToFile(ans, filename,milliseconds);
    printf("结果已输出至文件%s\n",filename);


    releaseCNF(&cnf);
    releaseAns(ans);
    return 0;
}


//子函数模块
        //1.读取CNF文件
int readCNFFile(CNF &cnf,int** count,char* filename) {
    printf("请输入CNF文件名: ");
    scanf("%s", filename);
    FILE *file = fopen(filename, "r");
    if(!file){
        printf("无法打开文件%s\n",filename);
        return ERROR;
    }
    char line[1024];
    while(fgets(line, sizeof(line), file)) {
        if(line[0] == 'c') continue;
        if(line[0] == 'p') {
            sscanf(line, "p cnf %d %d", &cnf.varcount, &cnf.clausecount);
            cnf.clauses = (clause *)malloc(cnf.clausecount * sizeof(clause));
             *count = (int*)calloc(cnf.varcount + 1, sizeof(int));
           
            for(int i=0; i<cnf.clausecount; i++) {
                cnf.clauses[i].literals = (int *)malloc(literalincrement * sizeof(int));
                cnf.clauses[i].literalcount = 0;
                int cap = literalincrement;
                int lit;
                while(fscanf(file, "%d", &lit) == 1 && lit != 0) {
                    if(cnf.clauses[i].literalcount >= cap) {
                        cap += literalincrement;
                        cnf.clauses[i].literals = (int *)realloc(cnf.clauses[i].literals, cap * sizeof(int));
                    }
                    cnf.clauses[i].literals[cnf.clauses[i].literalcount++] = lit;
                    (*count)[abs(lit)]++;
                }
            }
            break; // 只读取一次
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
    //不要 free(cnf); 如果是栈变量？？？？？？？？？？？？？？？？？？？？
}

        //5.打印最终结果解（以文件形式输出）
        // 输出文件规范：
        // 对每个算例的求解结果要求输出到一个与算例同名的文件（文件扩展名为.res），文件内容与格式要求如下：
        // s求解结果//1表示满足，0表示不满足，-1表示在限定时间内未完成求解
        // v -1 2 -3 … //满足时，每个变元的赋值序列，-1表示第一个变元1取假，2表示第二个变元取真，用空格分开，此处为示例。
        // t 17     //以毫秒为单位的DPLL执行时间，可增加分支规则执行次数信息
int printAnswerToFile(answer *ans, char *filename,int time){
    FILE *file=fopen(filename,"w");
    if(!file){
        return ERROR;
    }
    fprintf(file, "s %d\n", ans->assignments[0]); 
    fprintf(file, "v ");
    for(int i=1;i<=ans->varcount;i++){
        fprintf(file, "%d ", ans->assignments[i] > 0 ? i : -i);
    }
    fprintf(file, "\nt %d\n",time); 
    fclose(file);
    return OK;
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
    if(unsignedcount==1) return code;
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
                        if(var > 0){
                            ans->assignments[var] = 1;
                        }
                        else{
                            ans->assignments[-var] = -1;
                        }
                        state=1;
                        break;
                    }
            }
    }while (state); //存在单子句就继续传播
    return TRUE;    
}

int dpll(CNF *cnf,answer *ans,vars* find){

    if (!UintSpread(cnf, ans)) {
        return FALSE; 
    }
    
    // 检查是否所有子句都已满足
    int allsat=1;
    for(int i=0;i<cnf->clausecount;i++){
        clause *cl=&cnf->clauses[i];
        int b=isClauseOk(cl,ans);
        if(b==0) {allsat=0;break;}
        if(b==-1) {
            return FALSE; 
        }
    }
    if(allsat==1){
        ans->assignments[0] = 1; //标记为满足
        return TRUE; 
    }

    // 选择未赋值的变量
    int var=0;
    vars* temp=find;
    for(;temp!=NULL;temp=temp->next){
        if(ans->assignments[temp->var]==0) 
        {
            var=temp->var;
            break;
        }
    }

   // 尝试赋值为真
answer* anscopy = createAnswer(cnf->varcount);
memcpy(anscopy->assignments, ans->assignments, (cnf->varcount + 1) * sizeof(int));
anscopy->assignments[var] = 1;
if (dpll(cnf, anscopy,find)) {
    memcpy(ans->assignments, anscopy->assignments, (cnf->varcount + 1) * sizeof(int));
    releaseAns(anscopy);
    return TRUE;
}
releaseAns(anscopy);

// 尝试赋值为假
anscopy = createAnswer(cnf->varcount);
memcpy(anscopy->assignments, ans->assignments, (cnf->varcount + 1) * sizeof(int));
anscopy->assignments[var] = -1;
if (dpll(cnf, anscopy,find)) {
    memcpy(ans->assignments, anscopy->assignments, (cnf->varcount + 1) * sizeof(int));
    releaseAns(anscopy);
    return TRUE;
}
releaseAns(anscopy);
return FALSE;
}

//////辅助改进模块
vars *sortVar(int* count,int varcount){//按出现次数从大到小排序,返回空头指针
    vars *head=(vars *)malloc(sizeof(vars));
    head->var=0;
    head->next=NULL;
    for(int i=1;i<=varcount;i++){
        vars *newnode=(vars *)malloc(sizeof(vars));
        newnode->var=i;
        newnode->next=NULL;
        vars *p=head;
        // 出现次数多的排前面
        while(p->next!=NULL && count[p->next->var] < count[i]){
            p=p->next;
        }
        newnode->next=p->next;
        p->next=newnode;
    }
    return head;
}
