#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unordered_set>

// ====== 标准定义区 ======
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int KeyType;
typedef struct {
    KeyType key;
    char others[20];
} TElemType;

typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct {
    struct {
        char name[30];
        BiTree T;
    } elem[10];
    int length;
} BITREES;

// ====== 函数声明区 ======
status CreateBiTree(BiTree &T, TElemType definition[]);
status DestroyBiTree(BiTree &T);
status ClearBiTree(BiTree &T);
status BiTreeEmpty(BiTree T);
int BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree T, KeyType e);
status Assign(BiTree &T, KeyType e, TElemType value);
BiTNode* GetSibling(BiTree T, KeyType e);
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c);
status DeleteNode(BiTree &T, KeyType e);
status PreOrderTraverse(BiTree T, void (*visit)(BiTree));
status InOrderTraverse(BiTree T, void (*visit)(BiTree));
status PostOrderTraverse(BiTree T, void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree));

// 文件保存/加载函数声明
status SaveBiTreeToFile(BiTree T, const char* filename);
status LoadBiTreeFromFile(BiTree &T, const char* filename);

// 多二叉树管理
status AddBiTree(BITREES &Trees, char TreeName[]);
status RemoveBiTree(BITREES &Trees, char TreeName[]);
int LocateBiTree(BITREES Trees, char TreeName[]);
void printAllTreeNames(BITREES &Trees);

// ====== 附加功能声明 ======
int MaxPathSum(BiTree T);
BiTNode* LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2);
void InvertTree(BiTree &T);

// ====== 实现区 ======

// 用全局变量idx，每次CreateBiTree前赋值为0，CreateBiTree内部不再用static
int g_create_idx = 0;

// 修正CreateBiTree静态变量问题，每次Create前调用，避免多树和多次创建时静态变量未重置导致无法创建
void ResetCreateBiTreeStatic() {
    g_create_idx = 0;
}

// 创建二叉树（带空枝的先序序列，关键字唯一）
status CreateBiTree(BiTree &T, TElemType definition[]) {
    static std::unordered_set<KeyType> key_set;
    int &idx = g_create_idx;
    if(idx == 0) key_set.clear();
    if(definition[idx].key == -1 || definition[idx].key == 0) {
        T = NULL;
        idx++;
        return OK;
    }
    if(key_set.find(definition[idx].key) != key_set.end()) {
        idx = 0;
        return ERROR;
    }
    key_set.insert(definition[idx].key);
    T = (BiTNode*)malloc(sizeof(BiTNode));
    if(!T) {
        idx = 0;
        return OVERFLOW;
    }
    T->data = definition[idx++];
    status lres = CreateBiTree(T->lchild, definition);
    status rres = CreateBiTree(T->rchild, definition);
    // 递归出口时复原idx
    if(idx != 0 && (definition[idx].key == -1 || definition[idx].key == 0)) idx = 0;
    return (lres == OK && rres == OK) ? OK : ERROR;
}

// 销毁二叉树：树不存在，T==NULL
status DestroyBiTree(BiTree &T) {
    if(T == NULL) return ERROR;
    DestroyBiTree(T->lchild);
    DestroyBiTree(T->rchild);
    free(T);
    T = NULL;
    return OK;
}

// 清空二叉树：只释放所有结点，T指针本身不变，置为一个空节点
status ClearBiTree(BiTree &T) {
    if(T == NULL) return ERROR;
    DestroyBiTree(T->lchild);
    DestroyBiTree(T->rchild);
    T->lchild = NULL;
    T->rchild = NULL;
    // 也可以清空data
    T->data.key = 0;
    T->data.others[0] = '\0';
    return OK;
}

// 判空：树不存在返回-1，空树返回TRUE，否则FALSE
status BiTreeEmpty(BiTree T) {
    if(T == NULL) return -1; // 不存在
    if(T->lchild == NULL && T->rchild == NULL && T->data.key == 0 && T->data.others[0] == '\0')
        return TRUE; // 空树
    return FALSE;
}

// 求深度
int BiTreeDepth(BiTree T) {
    if(T == NULL) return 0;
    // 空树深度为0
    if(T->lchild == NULL && T->rchild == NULL && T->data.key == 0 && T->data.others[0] == '\0')
        return 0;
    int l = BiTreeDepth(T->lchild);
    int r = BiTreeDepth(T->rchild);
    return 1 + (l > r ? l : r);
}

// 查找结点
BiTNode* LocateNode(BiTree T, KeyType e) {
    if(T == NULL) return NULL;
    if(T->data.key == e) return T;
    BiTNode* lres = LocateNode(T->lchild, e);
    if(lres) return lres;
    BiTNode* rres = LocateNode(T->rchild, e);
    if(rres) return rres;
    return NULL;
}

// 辅助：将所有关键字存入mem
void to_mem(BiTree T, int mem[]) {
    if(T == NULL) return;
    mem[T->data.key] = 1;
    to_mem(T->lchild, mem);
    to_mem(T->rchild, mem);
}

// 结点赋值
status Assign(BiTree &T, KeyType e, TElemType value) {
    if(T == NULL) return ERROR;
    int mem[10000] = {0};
    to_mem(T, mem);
    if(value.key != e && mem[value.key] == 1) return ERROR;
    BiTNode* node = LocateNode(T, e);
    if(node == NULL) return ERROR;
    node->data = value;
    return OK;
}

// 获得兄弟结点
BiTNode* GetSibling(BiTree T, KeyType e) {
    if(T == NULL) return NULL;
    if(T->lchild && T->lchild->data.key == e) return T->rchild;
    if(T->rchild && T->rchild->data.key == e) return T->lchild;
    BiTNode* lres = GetSibling(T->lchild, e);
    if(lres) return lres;
    BiTNode* rres = GetSibling(T->rchild, e);
    if(rres) return rres;
    return NULL;
}

// 插入结点
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c) {
    if(T == NULL) return ERROR;
    if(LR != 0 && LR != 1 && LR != -1) return ERROR;
    if(LocateNode(T, c.key) != NULL) return ERROR;
    if(LR == -1) {
        BiTNode *newNode = (BiTNode*)malloc(sizeof(BiTNode));
        if(!newNode) return OVERFLOW;
        newNode->data = c;
        newNode->lchild = NULL;
        newNode->rchild = T;
        T = newNode;
        return OK;
    }
    BiTNode *node = LocateNode(T, e);
    if(node == NULL) return ERROR;
    if(LR == 0) {
        BiTNode *newNode = (BiTNode*)malloc(sizeof(BiTNode));
        if(!newNode) return OVERFLOW;
        newNode->data = c;
        newNode->lchild = NULL;
        newNode->rchild = node->lchild;
        node->lchild = newNode;
        return OK;
    } else if(LR == 1) {
        BiTNode *newNode = (BiTNode*)malloc(sizeof(BiTNode));
        if(!newNode) return OVERFLOW;
        newNode->data = c;
        newNode->lchild = NULL;
        newNode->rchild = node->rchild;
        node->rchild = newNode;
        return OK;
    }
    return ERROR;
}

// 删除结点
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

// 访问结点
void visit(BiTree T) {
    if(T->data.key != 0 || T->data.others[0] != '\0') // 空树不输出
        printf("%d,%s ", T->data.key, T->data.others);
}

// 前序遍历（非递归）
status PreOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    if(T == NULL) return ERROR;
    if(T->data.key == 0 && T->data.others[0] == '\0') return OK; // 空树
    BiTree stack[1000];
    int top = 0;
    stack[top++] = T;
    while(top > 0) {
        T = stack[--top];
        visit(T);
        if(T->rchild) stack[top++] = T->rchild;
        if(T->lchild) stack[top++] = T->lchild;
    }
    return OK;
}

// 中序遍历
status InOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    if(T == NULL) return ERROR;
    if(T->data.key == 0 && T->data.others[0] == '\0') return OK;
    InOrderTraverse(T->lchild, visit);
    visit(T);
    InOrderTraverse(T->rchild, visit);
    return OK;
}

// 后序遍历
status PostOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    if(T == NULL) return ERROR;
    if(T->data.key == 0 && T->data.others[0] == '\0') return OK;
    PostOrderTraverse(T->lchild, visit);
    PostOrderTraverse(T->rchild, visit);
    visit(T);
    return OK;
}

// 层序遍历
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    if(T == NULL) return ERROR;
    if(T->data.key == 0 && T->data.others[0] == '\0') return OK;
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
}

// ====== 文件保存/加载实现 ======
// 递归保存
void SaveTreeToFileRecursive(BiTree T, FILE* fp) {
    if(T == NULL) {
        TElemType nullElem = {-1, ""};
        fwrite(&nullElem, sizeof(TElemType), 1, fp);
        return;
    }
    fwrite(&T->data, sizeof(TElemType), 1, fp);
    SaveTreeToFileRecursive(T->lchild, fp);
    SaveTreeToFileRecursive(T->rchild, fp);
}
status SaveBiTreeToFile(BiTree T, const char* filename) {
    if(T == NULL) {
        printf("      二叉树不存在，无法保存！\n");
        return ERROR;
    }
    FILE *fp = fopen(filename, "wb");
    if(!fp) {
        printf("      文件打开失败！\n");
        return ERROR;
    }
    SaveTreeToFileRecursive(T, fp);
    fclose(fp);
    printf("      已保存到文件：%s\n", filename);
    return OK;
}
// 递归加载
status LoadTreeFromFileRecursive(BiTree &T, FILE* fp) {
    TElemType elem;
    if(fread(&elem, sizeof(TElemType), 1, fp) != 1) {
        return ERROR;
    }
    if(elem.key == -1) {
        T = NULL;
        return OK;
    }
    T = (BiTNode*)malloc(sizeof(BiTNode));
    if(!T) return OVERFLOW;
    T->data = elem;
    status lres = LoadTreeFromFileRecursive(T->lchild, fp);
    if(lres != OK) return lres;
    status rres = LoadTreeFromFileRecursive(T->rchild, fp);
    return rres;
}
status LoadBiTreeFromFile(BiTree &T, const char* filename) {
    FILE *fp = fopen(filename, "rb");
    if(!fp) {
        printf("      文件打开失败！\n");
        return ERROR;
    }
    if(T == NULL) {
        // 不存在则直接加载
        status res = LoadTreeFromFileRecursive(T, fp);
        fclose(fp);
        if(res == OK) {
            printf("      已从文件加载二叉树：%s\n", filename);
        } else {
            printf("      加载失败：文件内容无效！\n");
        }
        return res;
    } else {
        // 存在则清空
        ClearBiTree(T);
        status res = LoadTreeFromFileRecursive(T, fp);
        fclose(fp);
        if(res == OK) {
            printf("      已从文件加载二叉树：%s\n", filename);
        } else {
            printf("      加载失败：文件内容无效！\n");
        }
        return res;
    }
}

// ====== 多二叉树管理 ======
status AddBiTree(BITREES &Trees, char TreeName[]) {
    for(int i = 0; i < Trees.length; i++) {
        if(strcmp(Trees.elem[i].name, TreeName) == 0) {
            printf("      已存在同名二叉树！\n");
            return ERROR;
        }
    }
    if(Trees.length >= 10) {
        printf("      二叉树数量已达上限！\n");
        return ERROR;
    }
    Trees.elem[Trees.length].T = NULL;
    strcpy(Trees.elem[Trees.length].name, TreeName);
    Trees.length++;
    return OK;
}
status RemoveBiTree(BITREES &Trees, char TreeName[]) {
    if(Trees.length == 0) return ERROR;
    int i;
    for(i = 0; i < Trees.length; i++) {
        if(strcmp(Trees.elem[i].name, TreeName) == 0) break;
    }
    if(i == Trees.length) return ERROR;
    DestroyBiTree(Trees.elem[i].T);
    for(int j = i; j < Trees.length - 1; j++) {
        Trees.elem[j] = Trees.elem[j + 1];
    }
    Trees.length--;
    return OK;
}
int LocateBiTree(BITREES Trees, char TreeName[]) {
    if(Trees.length == 0) return 0;
    for(int i = 0; i < Trees.length; i++) {
        if(strcmp(Trees.elem[i].name, TreeName) == 0) return i + 1;
    }
    return ERROR;
}
void printAllTreeNames(BITREES &Trees) {
    printf("      当前已有二叉树数量：%d\n", Trees.length);
    for(int i = 0; i < Trees.length; i++) {
        printf("      %d. %s\n", i + 1, Trees.elem[i].name);
    }
}

// ====== 附加功能实现 ======

// 最大路径和：根到叶最大路径和
int MaxPathSum(BiTree T) {
    if(T == NULL) return 0;
    if(T->lchild == NULL && T->rchild == NULL)
        return T->data.key;
    int l = MaxPathSum(T->lchild);
    int r = MaxPathSum(T->rchild);
    return T->data.key + (l > r ? l : r);
}

// 最近公共祖先
BiTNode* LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2) {
    if(T == NULL) return NULL;
    if(T->data.key == e1 || T->data.key == e2) return T;
    BiTNode* l = LowestCommonAncestor(T->lchild, e1, e2);
    BiTNode* r = LowestCommonAncestor(T->rchild, e1, e2);
    if(l && r) return T;
    return l ? l : r;
}

// 翻转二叉树
void InvertTree(BiTree &T) {
    if(T == NULL) return;
    BiTree tmp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = tmp;
    InvertTree(T->lchild);
    InvertTree(T->rchild);
}

// 横向打印二叉树结构（根在左，右子树在上，左子树在下）
void PrintTree(BiTree T, int depth = 0) {
    if(T == NULL || (T->data.key == 0 && T->data.others[0] == '\0')) return;
    PrintTree(T->rchild, depth + 1);
    for(int i = 0; i < depth; ++i) printf("    ");
    printf("%d,%s\n", T->data.key, T->data.others);
    PrintTree(T->lchild, depth + 1);
}

// ====== 菜单与主控 ======
void singleTreeMenu() {
    printf("\n");
    printf("      ========== 单二叉树操作菜单 ==========\n");
    printf("      1. CreateBiTree        8. GetSibling\n");
    printf("      2. DestroyBiTree       9. InsertNode\n");
    printf("      3. ClearBiTree        10. DeleteNode\n");
    printf("      4. BiTreeEmpty        11. PreOrderTraverse\n");
    printf("      5. BiTreeDepth        12. InOrderTraverse\n");
    printf("      6. LocateNode         13. PostOrderTraverse\n");
    printf("      7. Assign             14. LevelOrderTraverse\n");
    printf("      15. MaxPathSum        16. LowestCommonAncestor\n");
    printf("      17. InvertTree        17. PrintTree\n");
    printf("      0. 返回多表菜单\n");
    printf("      =====================================\n");
    printf("      请选择你的操作[0~17]:");
}

void singleTreeControl(BiTree &T) {
    int op = 1;
    TElemType elem, c;
    KeyType e, e1, e2;
    int LR;
    while(op) {
        system("cls");
        singleTreeMenu();
        scanf("%d", &op);

        // 除创建，销毁，其他操作都要判断树是否存在
        if(op != 1 && op != 2 && T == NULL) {
            printf("      二叉树不存在！\n");
            getchar(); printf("      按任意键继续...\n"); getchar();
            continue;
        }

        switch(op) {
            case 1: {
                // 判断树是否存在，若存在需询问是否销毁覆盖
                if(T != NULL) {
                    printf("      当前二叉树已存在，是否销毁并覆盖？(y/n)：");
                    char ch;
                    getchar(); // 吸收上一个回车
                    ch = getchar();
                    if(ch != 'y' && ch != 'Y') {
                        printf("      已取消创建操作。\n");
                        printf("      按任意键继续...\n"); getchar();
                        break;
                    }
                    DestroyBiTree(T);
                }
                printf("      请输入带空枝的先序序列（格式：关键字 信息），以-1结束：\n");
                TElemType definition[100];
                int i = 0;
                do {
                    scanf("%d%s", &definition[i].key, definition[i].others);
                } while(definition[i++].key != -1);
                ResetCreateBiTreeStatic();
                if(CreateBiTree(T, definition) == OK) {
                    printf("      二叉树创建成功！\n");
                } else {
                    printf("      二叉树创建失败，存在重复关键字！\n");
                }
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 2: {
                if(T == NULL) printf("      二叉树不存在，无法销毁！\n");
                else if(DestroyBiTree(T) == OK) printf("      二叉树销毁成功！\n");
                else printf("      二叉树销毁失败！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 3: {
                if(T == NULL) printf("      二叉树不存在，无法清空！\n");
                else if(ClearBiTree(T) == OK) printf("      二叉树清空成功！\n");
                else printf("      二叉树清空失败！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 4: {
                int empty = BiTreeEmpty(T);
                if(empty == -1) printf("      二叉树不存在！\n");
                else if(empty == TRUE) printf("      二叉树为空！\n");
                else printf("      二叉树不为空！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 5: {
                printf("      二叉树的深度为：%d\n", BiTreeDepth(T));
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 6: {
                printf("      请输入要查找的结点关键字：");
                scanf("%d", &e);
                BiTNode* node = LocateNode(T, e);
                if(node) printf("      找到关键字为%d的结点，其信息为：%s\n", e, node->data.others);
                else printf("      未找到关键字为%d的结点！\n", e);
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 7: {
                printf("      请输入要赋值的结点关键字：");
                scanf("%d", &e);
                printf("      请输入新关键字和信息：");
                scanf("%d %s", &elem.key, elem.others);
                if(Assign(T, e, elem) == OK) printf("      结点赋值成功！\n");
                else printf("      结点赋值失败，可能是关键字不存在或新关键字已存在！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 8: {
                printf("      请输入要查找兄弟的结点关键字：");
                scanf("%d", &e);
                BiTNode* sibling = GetSibling(T, e);
                if(sibling) printf("      找到兄弟结点，其关键字为%d，信息为：%s\n", sibling->data.key, sibling->data.others);
                else printf("      未找到关键字为%d的结点的兄弟！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 9: {
                printf("      请输入插入位置的父节点关键字：");
                scanf("%d", &e);
                printf("      请输入位置(0-左,1-右,-1-根)：");
                scanf("%d", &LR);
                printf("      请输入要插入的结点值（关键字 信息）：");
                scanf("%d %s", &c.key, c.others);
                if(InsertNode(T, e, LR, c) == OK) printf("      结点插入成功！\n");
                else printf("      结点插入失败！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 10: {
                printf("      请输入要删除的结点关键字：");
                scanf("%d", &e);
                if(DeleteNode(T, e) == OK) printf("      结点删除成功！\n");
                else printf("      结点删除失败，可能不存在该关键字！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 11: {
                printf("      前序遍历结果：\n      ");
                PreOrderTraverse(T, visit);
                printf("\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 12: {
                printf("      中序遍历结果：\n      ");
                InOrderTraverse(T, visit);
                printf("\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 13: {
                printf("      后序遍历结果：\n      ");
                PostOrderTraverse(T, visit);
                printf("\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 14: {
                printf("      层序遍历结果：\n      ");
                LevelOrderTraverse(T, visit);
                printf("\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 15: { // MaxPathSum
                int sum = MaxPathSum(T);
                printf("      根到叶最大路径和为：%d\n", sum);
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 16: { // LowestCommonAncestor
                printf("      请输入两个结点的关键字：");
                scanf("%d%d", &e1, &e2);
                BiTNode* lca = LowestCommonAncestor(T, e1, e2);
                if(lca)
                    printf("      最近公共祖先关键字为：%d，信息为：%s\n", lca->data.key, lca->data.others);
                else
                    printf("      未找到最近公共祖先！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 17: { // InvertTree
                InvertTree(T);
                printf("      二叉树已翻转！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 18: { // PrintTree
                printf("      二叉树结构：\n");
                PrintTree(T);
                printf("\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 0:
                break;
            default:
                printf("      输入有误，请重新输入！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
        }
    }
}

void multiTreeMenu() {
    printf("\n");
    printf("      ========== 多二叉树管理菜单 ==========\n");
    printf("      1. 新建二叉树\n");
    printf("      2. 删除二叉树\n");
    printf("      3. 打印所有二叉树名\n");
    printf("      4. 进入某个二叉树操作\n");
    printf("      5. 保存二叉树到文件\n");
    printf("      6. 从文件加载二叉树\n");
    printf("      0. 退出系统\n");
    printf("      =====================================\n");
    printf("      请选择你的操作[0~4]:");
}

int main(void) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    BITREES Trees = {0};
    int op = 1;
    char name[30];
    int pos;
    while(op) {
        system("cls");
        multiTreeMenu();
        scanf("%d", &op);
        switch(op) {
            case 1:
                printf("      请输入新二叉树的名称：");
                scanf("%s", name);
                if(AddBiTree(Trees, name) == OK) printf("      新建二叉树成功！\n");
                else printf("      新建二叉树失败！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            case 2:
                printf("      请输入要删除的二叉树名称：");
                scanf("%s", name);
                if(RemoveBiTree(Trees, name) == OK) printf("      删除二叉树成功！\n");
                else printf("      删除二叉树失败，可能不存在该二叉树！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            case 3:
                printAllTreeNames(Trees);
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            case 4:
                printf("      请输入要操作的二叉树名称：");
                scanf("%s", name);
                pos = LocateBiTree(Trees, name);
                if(pos > 0) {
                    printf("      进入二叉树 [%s] 的操作\n", name);
                    singleTreeControl(Trees.elem[pos-1].T);
                } else {
                    printf("      二叉树 [%s] 不存在！\n", name);
                    getchar(); printf("      按任意键继续...\n"); getchar();
                }
                break;
            // ========== 文件保存/加载功能 ==========
            case 5: // 保存某表到文件
                printf("      请输入要保存的二叉树名称：");
                scanf("%s", name);
                pos = LocateBiTree(Trees, name);
                if(pos > 0) {
                    printf("      请输入文件名：");
                    char filename[100];
                    scanf("%s", filename);
                    if(SaveBiTreeToFile(Trees.elem[pos-1].T, filename) == OK) {
                        printf("      保存二叉树成功！\n");
                    } else {
                        printf("      保存二叉树失败！\n");
                    }
                } else {
                    printf("      二叉树 [%s] 不存在！\n", name);
                }
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            case 6: // 从文件加载到某表
                printf("      请输入要加载到的二叉树名称：");
                scanf("%s", name);
                pos = LocateBiTree(Trees, name);
                if(pos > 0) {
                    // 判断树是否存在，若存在需询问是否销毁覆盖
                    if(Trees.elem[pos-1].T != NULL) {
                        printf("      当前二叉树已存在，是否销毁并覆盖？(y/n)：");
                        char ch;
                        getchar(); // 吸收上一个回车
                        ch = getchar();
                        if(ch != 'y' && ch != 'Y') {
                            printf("      已取消加载操作。\n");
                            printf("      按任意键继续...\n"); getchar();
                            break;
                        }
                        DestroyBiTree(Trees.elem[pos-1].T);
                    }
                    printf("      请输入文件名：");
                    char filename[100];
                    scanf("%s", filename);
                    if(LoadBiTreeFromFile(Trees.elem[pos-1].T, filename) == OK) {
                        printf("      加载二叉树成功！\n");
                    } else {
                        printf("      加载二叉树失败！\n");
                    }
                } else {
                    printf("      二叉树 [%s] 不存在！\n", name);
                }
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            case 0:
                for(int i = 0; i < Trees.length; i++) DestroyBiTree(Trees.elem[i].T);
                printf("      感谢使用二叉树管理系统，再见！\n");
                break;
            default:
                printf("      输入有误，请重新输入！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
        }
    }
    return 0;
}