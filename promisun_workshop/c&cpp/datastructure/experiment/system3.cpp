#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//前置定义
    #define MAX_TREES 10
    #define TRUE 1
    #define FALSE 0
    #define OK 1
    #define ERROR 0
    #define INFEASIBLE -1
    #define OVERFLOW -2

    typedef int status;
    typedef int KeyType; 

    typedef struct {
            KeyType  key;
            char others[20];
    } TElemType; //二叉树结点类型定义
    
    typedef struct {
    int pos;
    TElemType data;
    } DEF;//定义创建二叉树时输入的结点类型

    typedef struct BiTNode{  //二叉链表结点的定义
            TElemType  data;
            struct BiTNode *lchild,*rchild;
    } BiTNode, *BiTree;

    typedef struct {
        char name[30];
        BiTree T;
    } TreeEntry;// 单个二叉树

    typedef struct {
        TreeEntry trees[MAX_TREES];
        int length;
    } TreeList;// 多二叉树管理表

    //函数声明
    status CreateBiTree(BiTree &T, DEF definition[]);
    void visit(BiTree T);
    status DestroyBiTree(BiTree &T);
    status ClearBiTree(BiTree &T);
    status BiTreeEmpty(BiTree T);
    int BiTreeDepth(BiTree T);
    BiTNode* LocateNode(BiTree T, KeyType e);
    status Assign(BiTree &T, KeyType e, TElemType value,int mem[]);
    status to_mem(BiTree T,int mem[]);
    BiTNode* GetSibling(BiTree T, KeyType e);
    status InsertNode(BiTree &T, KeyType e, int LR, TElemType c);
    status DeleteNode(BiTree &T, KeyType e);
    status PreOrderTraverse(BiTree T, void (*visit)(BiTree));
    status InOrderTraverse(BiTree T, void (*visit)(BiTree));
    status PostOrderTraverse(BiTree T, void (*visit)(BiTree),int memo[]);
    status LevelOrderTraverse(BiTree T, void (*visit)(BiTree));
    void SaveTreeNode(BiTree T, FILE* fp);
    status SaveBiTree(BiTree T, char FileName[]);
    status LoadTreeNode(BiTree &T,FILE* fp);
    status LoadBiTree(BiTree &T,char FileName[]);
    status MaxPathSum(BiTree T);
    void InvertTree(BiTree &T);
    BiTNode* LowestCommonAncestor(BiTree T,KeyType e1,KeyType e2);
    void SingleTreeMenu(BiTree &T, char name[]);

//框架构建
    int main() {
        int op = 1;
        char name[30];
        TElemType def[100];
        char filename[100];
        TreeList a;
        a.length=0;

        while (op) {
            system("cls");
            printf("\n\n");
            printf("      Menu for Binary Tree Management System\n");
            printf("-----------------------------------------------------\n");
            printf("        1. AddTree           4. SingleTree\n");
            printf("        2. RemoveTree        5. TreesTraverse(preorder)\n");
            printf("        3. LocateTree        0. Exit\n");
            printf("-----------------------------------------------------\n");
            printf("    请选择你的操作[0~5]:");
            scanf("%d", &op);
            switch (op) {
                case 1:{
                    printf("请输入二叉树名称：\n");
                    scanf("%s", name);
                    if (a.length++ >= MAX_TREES) {
                        printf("空间已满，无法再创建二叉树！\n");
                        getchar(); getchar();
                        break;
                    }
                //下列输入为结点在满二叉树中的编号和结点值的序列，当结点在满二叉树中的编号为0时表示输入结束。
                //0 0 null代表结束标记。
                    DEF definition[100];
                    int memorey[100]={0};
                    BiTree T;
                    int ans=0,w=0,ok=1;
                    printf("请输入二叉树：（结点在满二叉树中的编号和结点值的关键字{不能重复}、其他内容，0 0 null代表结束标记。）\n"); 
                    do {
                        scanf("%d%d%s",&definition[w].pos,&definition[w].data.key,definition[w].data.others);
                        if(memorey[definition[w].data.key]) ok=0;
                        memorey[definition[w].data.key]=1;
                    } while (definition[w++].pos);
                    if(!ok) {
                    	printf("二叉树创建失败(关键字重复)！\n");
                    	getchar(); getchar();
                    break;
					}
                    ans=CreateBiTree(T,definition);
                    if (ans == OK) {
                        printf("二叉树创建成功！\n");
                        a.trees[a.length - 1].T = T;
                        strcpy(a.trees[a.length - 1].name, name);
                    } else {
                        printf("二叉树创建失败！\n");
                        a.length--;
                    }
                    getchar(); getchar();
                    break;
            	}
                case 2:
                    printf("请输入要删除的二叉树名称：\n");
                    scanf("%s", name);
                    for (int i = 0; i < a.length; i++) {
                        if (strcmp(a.trees[i].name, name) == 0) {
                            DestroyBiTree(a.trees[i].T);
                            for (int j = i; j < a.length - 1; j++)
                                a.trees[j] = a.trees[j + 1];
                            a.length--;
                            printf("该二叉树删除成功！\n");
                            goto label1; 
                        }
                    }
                    printf("未找到该二叉树，无法删除！\n");
        label1:            getchar(); getchar();
                    break;
                case 3:
                    printf("请输入要查找的二叉树名称：\n");
                    scanf("%s", name);
                    for (int i = 0; i < a.length; i++) {
                        if (strcmp(a.trees[i].name, name) == 0) {
                            printf("二叉树 %s 的逻辑序号为：%d\n", name, i + 1);
                            goto label2; 
                        }
                    }
                    printf("未找到该二叉树！\n");
        label2:            getchar(); getchar();
                    break;
                case 4:
                    printf("对哪一个树展开更多单一操作（输入逻辑编号即可）？\n");
                    int idx2;
                    scanf("%d", &idx2);
                    if (idx2 < 1 || idx2 > a.length) {
                        printf("输入的逻辑编号不合法！\n");
                        getchar(); getchar();
                        break;
                    }
                    SingleTreeMenu(a.trees[idx2 - 1].T,a.trees[idx2 - 1].name);
                    if(a.trees[idx2 - 1].T==NULL) {
                    	for (int j = idx2 - 1; j < a.length - 1; j++)
                                a.trees[j] = a.trees[j + 1];
                            a.length--;
					}
                    break;
                case 5:
                    for (int i = 0; i < a.length; i++) {
                        printf("%s: ", a.trees[i].name);
                        PreOrderTraverse(a.trees[i].T,visit);
                        printf("\n");
                    }
                    getchar(); getchar();
                    break;
                case 0:
                    break;
            }
        }
        printf("欢迎下次再使用本系统！\n");
        return 0;
    }

    void SingleTreeMenu(BiTree &T, char name[]) {
        int op = 1;
        while (op) {
            system("cls");
            printf("\n\n");
            printf("      Menu for Single Binary Tree [%s]\n", name);
            printf("-----------------------------------------------------\n");
            printf("   1. PreOrderTraverse      9. InsertNode \n");
            printf("   2. InOrderTraverse       10. DeleteNode\n");
            printf("   3. PostOrderTraverse     11. SaveBiTree\n");
            printf("   4. LevelOrderTraverse    12. LoadBiTree\n");
            printf("   5. DestroyBiTree         13. InvertTree\n");
            printf("   6. ClearBiTree           14. LowestCommonAncestor\n");
            printf("   7. BiTreeDepth           15. MaxPathSum\n");
            printf("   8. Assign                16. GetSibling\n");
            printf("   0. Exit\n");
            printf("-----------------------------------------------------\n");
            printf("请选择你的操作[0~13]:");
            scanf("%d", &op);
            switch (op) {
                case 1:
                    PreOrderTraverse(T, visit);
                    printf("\n"); getchar(); getchar();
                    break;
                case 2:
                    InOrderTraverse(T, visit);
                    printf("\n"); getchar(); getchar();
                    break;
                case 3: {
                    int memo[1000] = {0};
                    PostOrderTraverse(T, visit, memo);
                    printf("\n"); getchar(); getchar();
                    break;
                }
                case 4:
                    LevelOrderTraverse(T, visit);
                    printf("\n"); getchar(); getchar();
                    break;
                case 5:
                    DestroyBiTree(T);
                    printf("已销毁！\n"); getchar(); getchar();
                    break;
                case 6:
                	if(T==NULL) {
                		printf("二叉树不存在，无法清空！");
                		getchar(); getchar();
                    break;
					}
                    ClearBiTree(T);
                    printf("已清空！\n"); getchar(); getchar();
                    break;
                case 7:
                    printf("树深度为：%d\n", BiTreeDepth(T));
                    getchar(); getchar();
                    break;
                case 8: {			/*注意单树销毁后的情况修正*/
                	if(T==NULL) {
                		printf("二叉树不存在！");
                		getchar(); getchar();
                    break;
					}
                    printf("请输入要赋值的结点key：");
                    int k;
                    scanf("%d", &k);
                    printf("请输入新值(key others)：");
                    TElemType v;
                    scanf("%d%s", &v.key, v.others);
                    int mem[100] = {0};
                    to_mem(T, mem);
                    if (Assign(T, k, v, mem) == OK)
                        printf("赋值成功！\n");
                    else
                        printf("赋值失败（关键字冲突或不存在）！\n");
                    getchar(); getchar();
                    break;
                }
                case 9 : {
                	if(T==NULL) {
                		printf("二叉树不存在，无法插入！");
                		getchar(); getchar();
                    break;
					}
					int LR;KeyType e=1;TElemType c;
					printf("请输入要插入节点的父母节点关键字、插入位置（0左1右-1为根结点插入）、待插入节点的关键字和内容！\n"); 
					scanf("%d%d%d%s",&e,&LR,&c.key,c.others);
					int ans=InsertNode(T,e,LR,c);
					if(ans==OK) printf("插入结点成功！");
					else printf("插入结点失败！");
					getchar(); getchar();
                    break;
                }
                case 10: {
                	if(T==NULL) {
                		printf("二叉树不存在！");
                		getchar(); getchar();
                    break;
					}
                    printf("请输入要删除的结点key：");
                    int k;
                    scanf("%d", &k);
                    if (DeleteNode(T, k) == OK)
                        printf("删除成功！\n");
                    else
                        printf("删除失败！\n");
                    getchar(); getchar();
                    break;
                }
                case 11: {
                	if(T==NULL) {
                		printf("二叉树不存在,无法保存！");
                		getchar(); getchar();
                    break;
					}
                    printf("请输入文件名：");
                    char fname[100];
                    scanf("%s", fname);
                    if (SaveBiTree(T, fname) == OK)
                        printf("保存成功！\n");
                    else
                        printf("保存失败！\n");
                    getchar(); getchar();
                    break;
                }
                case 12: {
                	if(T!=NULL) {
                		printf("二叉树已存在，无法录入！");
                		getchar(); getchar();
                    break;
					}
                    printf("请输入文件名：");
                    char fname[100];
                    scanf("%s", fname);
                    if (LoadBiTree(T, fname) == OK)
                        printf("读取成功！\n");
                    else
                        printf("读取失败！\n");
                    getchar(); getchar();
                    break;
                }
                case 13:
                	if(T==NULL) {
                		printf("二叉树不存在！");
                		getchar(); getchar();
                    break;
					}
                    InvertTree(T);
                    printf("已反转！\n"); getchar(); getchar();
                    break;
                case 14: {
                	if(T==NULL) {
                		printf("二叉树不存在！/n");
                		getchar(); getchar();
                    break;
					}
                    printf("请输入两个结点key：");
                    int k1, k2;
                    scanf("%d %d", &k1, &k2);
                    BiTNode* lca = LowestCommonAncestor(T, k1, k2);
                    if (lca)
                        printf("最近公共祖先key为：%d", lca->data.key);
                    else
                        printf("未找到！\n");
                    getchar(); getchar();
                    break;
                }
                case 15:
                	if(T==NULL) {
                		printf("二叉树不存在！");
                		getchar(); getchar();
                    break;
					}
                    printf("最大路径和为：%d\n", MaxPathSum(T));
                    getchar(); getchar();
                    break;
                case 16: {
                	if(T==NULL) {
                		printf("二叉树不存在！/n");
                		getchar(); getchar();
                    break;
					}
                    printf("请输入结点key：");
                    int k;
                    scanf("%d", &k);
                    BiTNode* lca = GetSibling(T,k);
                    if (lca)
                        printf("兄弟结点key为：%d", lca->data.key);
                    else
                        printf("未找到！\n");
                    getchar(); getchar();
                    break;
                }
                case 0:
                    break;
            }
        }
    }


//基础函数实现

//创建二叉树
status CreateBiTree(BiTree &T,DEF definition[])
{
    int i=0,j;
    static BiTNode *p[100];
    while (j=definition[i].pos)
    {
        p[j]=(BiTNode *)malloc(sizeof(BiTNode));
        p[j]->data=definition[i].data;
        p[j]->lchild=NULL;
        p[j]->rchild=NULL;
        if (j!=1)
       		if (j%2)   p[j/2]->rchild=p[j];  
       	    else      p[j/2]->lchild=p[j];
        i++;
    }
    T=p[1];
    return OK;
}

//访问节点
void visit(BiTree T) {
    if(T->data.key != 0 || T->data.others[0] != '\0') // 空树不输出
        printf("%d,%s ", T->data.key, T->data.others);
}

//销毁二叉树
status DestroyBiTree(BiTree &T)
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return ERROR;
    DestroyBiTree(T->lchild);
    DestroyBiTree(T->rchild);
    free(T);
    T = NULL;
    return OK;
    /********** End **********/
}

//清空二叉树
status ClearBiTree(BiTree &T)
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T==NULL) return ERROR;
    ClearBiTree(T->lchild);
    ClearBiTree(T->rchild);
    T->data.key = 0;
    T->data.others[0] = '\0';
    return OK;
    /********** End **********/
}

//求深度
int BiTreeDepth(BiTree T)
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return 0;
    return 1 + (BiTreeDepth(T->lchild)>=BiTreeDepth(T->rchild)? BiTreeDepth(T->lchild) : BiTreeDepth(T->rchild));
    /********** End **********/
}

//查找结点
BiTNode* LocateNode(BiTree T,KeyType e)
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T==NULL) return NULL;
    if(T->data.key==e) return T;
    BiTNode*left=LocateNode(T->lchild,e);
    if(left) return left;
    BiTNode*right=LocateNode(T->rchild,e);
    if(right) return right;
    return NULL;
    /********** End **********/
}

//辅助函数：将所有关键字存入mem
status to_mem(BiTree T,int mem[])
{
    if(T == NULL) return OK;
    mem[T->data.key] = 1;
    to_mem(T->lchild, mem);
    to_mem(T->rchild, mem);
    return OK;
}

//实现结点赋值
status Assign(BiTree &T,KeyType e,TElemType value,int mem[])
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    BiTNode* p=LocateNode(T,e);
    if(p==NULL || (value.key!=e && mem[value.key])) return ERROR;

    mem[e] = 0;
    mem[value.key] = 1;
    p->data=value;
    return OK;

    /********** End **********/
}

//实现获得兄弟结点
BiTNode* GetSibling(BiTree T,KeyType e)
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return NULL;
    if(T->lchild && T->lchild->data.key == e) return T->rchild;
    if(T->rchild && T->rchild->data.key == e) return T->lchild;
    BiTNode* lres = GetSibling(T->lchild, e);
    if(lres) return lres;
    BiTNode* rres = GetSibling(T->rchild, e);
    if(rres) return rres;
    return NULL;
    /********** End **********/
}

//插入结点
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    /*功能说明：e是和T中结点关键字类型相同的给定值，LR为0或1，c是待插入结点；根据LR为0或者1，插入结点c到T中，作为关键字为e的结点的左或右孩子结点，结点e的原有左子树或右子树则为结点c的右子树，返回OK。如果插入失败，返回ERROR。
特别地，当LR为-1时，作为根结点插入，原根结点作为c的右子树。*/
	int meme[100]={0};
	to_mem(T,meme); 
    if(T == NULL || meme[c.key]==1) return ERROR;
    BiTNode* New=(BiTNode *)malloc(sizeof(BiTNode));
    New->data = c;
    New->lchild = NULL;
    if(LR == -1)
    {
        New->rchild = T;
        T = New;
        return OK;
    }
    BiTNode* a=LocateNode(T,e);
    if(a == NULL) return ERROR;
    if(LR == 0)
    {
        New->rchild = a->lchild;
        a->lchild = New;
        return OK;
    }
    else if(LR == 1)
    {
        New->rchild = a->rchild;
        a->rchild = New;
        return OK;
    }
    else return ERROR;
    /********** End **********/
}

//删除结点
status DeleteNode(BiTree &T, KeyType e) {
    if(T == NULL) return ERROR;
    if(T->data.key == e) {
        BiTNode *del = T;
        if(T->lchild == NULL && T->rchild == NULL) {
            // 如果是根节点且无子树，清空为“空树”而不是销毁
            T->data.key = 0;
            T->data.others[0] = '\0';
            return OK;
        } else if(T->lchild == NULL) {
            T = T->rchild;
        } else if(T->rchild == NULL) {
            T = T->lchild;
        } else {
            BiTNode *p = T->lchild;
            while(p->rchild != NULL) p = p->rchild;
            p->rchild = T->rchild;
            T = T->lchild;
        }
        free(del);
        return OK;
    }
    if(T->lchild && DeleteNode(T->lchild, e) == OK) return OK;
    if(T->rchild && DeleteNode(T->rchild, e) == OK) return OK;
    return ERROR;
}

//先序遍历
status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return ERROR;
    if(T->data.key == 0 && T->data.others[0] == '\0') return OK;
    visit(T);
    PreOrderTraverse(T->lchild, visit);
    PreOrderTraverse(T->rchild, visit);
    return OK;
    /********** End **********/
}

//中序遍历
status InOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return ERROR;
    if(T->data.key == 0 && T->data.others[0] == '\0') return OK;
    InOrderTraverse(T->lchild, visit);
    visit(T);
    InOrderTraverse(T->rchild, visit);
    return OK;
    /********** End **********/
}

//后序遍历
status PostOrderTraverse(BiTree T,void (*visit)(BiTree),int memo[])
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return ERROR;
    BiTree stack[1000];
    int top = 0;
    stack[top++] = T;
    if(T->rchild) stack[top++]=T->rchild;
    if(T->lchild) stack[top++]=T->lchild;
    while(top > 0 ) {
    T = stack[top-1];
    int ldone = (T->lchild == NULL) ? 1 : memo[T->lchild->data.key];
    int rdone = (T->rchild == NULL) ? 1 : memo[T->rchild->data.key];
    if(ldone && rdone) {
        visit(T);
        memo[T->data.key]=1;
        top--;
        continue;
    }
    if(T->rchild) stack[top++] = T->rchild;
    if(T->lchild) stack[top++] = T->lchild;
}
    return OK;
    /********** End **********/
}
//出现段错误（Segmentation Fault）的原因
// 在访问T->rchild->data.key或T->lchild->data.key时，如果T->rchild或T->lchild为NULL，就会解引用空指针，导致段错误。

// 正确写法
// 在访问T->rchild->data.key或T->lchild->data.key前，必须先判断指针是否为NULL。


//层次遍历
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(T == NULL) return ERROR;
    BiTree queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = T;
    while(front < rear) {
        T = queue[front++];
        visit(T);
        if(T->lchild) queue[rear++] = T->lchild;
        if(T->rchild) queue[rear++] = T->rchild;
    }
    return OK;
    /********** End **********/
}


//保存二叉树
void SaveTreeNode(BiTree T, FILE* fp) {
    if(T == NULL) {
        TElemType temp = {-1, ""};
        fwrite(&temp, sizeof(TElemType), 1, fp);
        return;
    }
    fwrite(&T->data, sizeof(TElemType), 1, fp);
    SaveTreeNode(T->lchild, fp);
    SaveTreeNode(T->rchild, fp);
}
status SaveBiTree(BiTree T, char FileName[])
    //将二叉树的结点数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if(T==NULL){
        printf("二叉树不存在，无法保存！\n");
        return ERROR;
    }
    FILE *fp=fopen(FileName,"w");
    if(fp==NULL) {
        printf("文件打开失败！\n");
        return ERROR;
    }
    SaveTreeNode(T,fp);
    fclose(fp);
    printf("已保存到文件：%s\n",FileName);
    return OK;
    /********** End 1 **********/
}


//加载二叉树
status LoadTreeNode(BiTree &T,FILE* fp){
    TElemType temp;
    if(fread(&temp,sizeof(TElemType),1,fp)!=1) return ERROR;
    if(temp.key==-1){
        T=NULL;
        return OK;
    }
    T=(BiTNode*)malloc(sizeof(BiTNode));   
    T->data=temp;
    status lstatus=LoadTreeNode(T->lchild,fp);
    status rstatus=LoadTreeNode(T->rchild,fp);
    if(lstatus==OK && rstatus==OK) return OK;
    else return ERROR;
}
status LoadBiTree(BiTree &T,  char FileName[])
    //读入文件FileName的结点数据，创建二叉树
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    if(T != NULL)  printf("二叉树已存在，请先销毁!\n");
    FILE *fp=fopen(FileName,"r");
    if(!fp){
        printf("文件打开失败!\n");
        return ERROR;
    }
    status result=LoadTreeNode(T,fp);
    fclose(fp);
    if(result == OK){
        printf("二叉树创建成功！\n");
        return OK;
    }
    else{
        printf("二叉树创建失败！\n");
        return ERROR;
    }
    /********** End 2 **********/
}

//最大子路径和
int MaxPathSum(BiTree T) {
    if(T == NULL) return 0;
    if(T->lchild == NULL && T->rchild == NULL)
        return T->data.key;
    int l = MaxPathSum(T->lchild);
    int r = MaxPathSum(T->rchild);
    return T->data.key + (l > r ? l : r);
}

//反转二叉树
void InvertTree(BiTree &T) {
    if(T == NULL) return;
    BiTree temp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = temp;
    InvertTree(T->lchild);
    InvertTree(T->rchild);
}

//最近公共祖先
BiTNode* LowestCommonAncestor(BiTree T,KeyType e1,KeyType e2){
    if(T == NULL) return NULL;
    if(T->data.key == e1 || T->data.key == e2) return T;
    BiTNode* left = LowestCommonAncestor(T->lchild, e1, e2);
    BiTNode* right = LowestCommonAncestor(T->rchild, e1, e2);
    if(left && right) return T;
    return left ? left : right;
}
