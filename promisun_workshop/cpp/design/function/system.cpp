#include "satpro.hpp"
int xian=0;


int satmain(){
    SetConsoleOutputCP(65001);
    clock_t start, end;
    int milliseconds;
    
    CNF cnf;
    int* count;
    char filename[100];
    char ansname[100];

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
    strcpy(ansname,filename);
    for(;ansname[i]!='.';i++);
    ansname[i+1]='r';ansname[i+2]='e';ansname[i+3]='s';ansname[i+4]='\0';


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
    if(!xian){
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
    }
        //打印至文件
    printAnswerToFile(ans, filename,milliseconds);
    if(!xian) printf("结果已输出至文件%s\n",ansname);

    releaseCNF(&cnf);
    releaseAns(ans);
    printf("验证？\n");
    int opt=0;
    printf("1.verify.exe  2.verify5000.exe  0.不验证\n");
    scanf("%d",&opt);
    if(opt==1){
        char command[150];
        sprintf(command, "verify.exe %s %s", filename, ansname);
        system(command);
    }
    else if(opt==2){
        char command[150];
        sprintf(command, "verify5000.exe %s", filename, ansname);
        system(command);
    }
    return 0;
}


int shudumain() {

    char shuduname[100];
    int grid[N][N];
    printf("请输入要生成的cnf文件名:\n");
    scanf("%s",shuduname);
    printf("请输入9x9数独（每行9个字符，空格用'.'表示）：\n");
    for (int i = 0; i < 9; i++) {
        char line[16];
        scanf("%15s", line);
        for (int j = 0; j < 9; j++) {
            if (line[j] == '.') grid[i][j] = 0;
            else grid[i][j] = line[j] - '0';
        }
    }
    shuduToCnf(grid, shuduname);
    xian=1;
    satmain();
    int answer[N][N] = {0};
    int a=0;
    for(;shuduname[a]!='.';a++);
    shuduname[a+1]='r';shuduname[a+2]='e';shuduname[a+3]='s';shuduname[a+4]='\0';
    int ok=analySat(shuduname , answer);
    if(ok==0 ||ok==-1){
        if(ok==0)printf("该数独无解！\n");
        xian=0;
        return 0;
    }
    printf("数独解：\n");
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++){
            // if(answer[i][j]==0) printf("9 ");
            //else
            printf("%d ", answer[i][j]);
        }
        printf("\n");
    }
    xian=0;
    return 1;
}


int main(){
    SetConsoleOutputCP(65001);
    int op=1;

    while(op){
         system("cls");	printf("\n\n");
        printf("1.dpll求解SAT问题       2.数独求解       0.退出\n");
        printf("请选择你的操作[0~2]:");
        scanf("%d",&op);
        switch(op){
            case 1:
                satmain();
                getchar();
                getchar();
                break;
            case 2:
                shudumain();
                getchar();
                getchar();
                break;
        }
    }
    printf("欢迎下次使用！\n");
    return 0;
}