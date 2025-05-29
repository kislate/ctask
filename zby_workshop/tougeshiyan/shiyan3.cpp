#include "stdio.h"
#include "stdlib.h"
#include "string.h"

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

typedef struct BiTNode {  //二叉链表结点的定义
    TElemType  data;
    struct BiTNode* lchild, * rchild;
} BiTNode, * BiTree;

#define MAX_TREES 10

typedef struct {
    char name[30];
    BiTree T;
} NamedTree;

typedef struct {
    NamedTree trees[MAX_TREES];
    int length;
} TreeList;

void PrintNode(BiTree T) {
    if (T) printf("%d ", T->data.key);
}

status CreateBiTree(BiTree& T, TElemType definition[]) {
    static KeyType mem[10000] = { 0 };
    static int index = 0;
    if (definition[index].key == -1 || definition[index].key == 0) {
        T = NULL;
        index++;
        return OK;
    }
    if (mem[definition[index].key] == 1) {
        return ERROR;
    }
    mem[definition[index].key] = 1;
    T = (BiTNode*)malloc(sizeof(BiTNode));
    if (!T) return OVERFLOW;
    T->data = definition[index++];
    status lres = CreateBiTree(T->lchild, definition);
    status rres = CreateBiTree(T->rchild, definition);
    return (lres == OK && rres == OK);
}

status DestroyBiTree(BiTree& T) {
    if (T == NULL) return OK;
    DestroyBiTree(T->lchild);
    DestroyBiTree(T->rchild);
    free(T);
    T = NULL;
    return OK;
}

status ClearBiTree(BiTree& T) {
    if (T == NULL) {
        return OK;
    }
    ClearBiTree(T->lchild);
    ClearBiTree(T->rchild);
    free(T);
    T = NULL;
    return OK;
}

status BiTreeEmpty(BiTree T) {
    return T == NULL ? TRUE : FALSE;
}


int BiTreeDepth(BiTree T) {
    if (T == NULL) {
        return 0;
    }
    int leftDepth = BiTreeDepth(T->lchild);
    int rightDepth = BiTreeDepth(T->rchild);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

BiTNode* LocateNode(BiTree T, KeyType e) {
    if (T == NULL) return NULL;
    if (T->data.key == e) return T;
    BiTNode* lres = LocateNode(T->lchild, e);
    if (lres) return lres;
    BiTNode* rres = LocateNode(T->rchild, e);
    if (rres) return rres;
    return NULL;
}

int mem[10000] = { 0 };
status to_mem(BiTree T) {
    if (T == NULL) return OK;
    mem[T->data.key] = 1;
    to_mem(T->lchild);
    to_mem(T->rchild);
    return OK;
}

status Assign(BiTree& T, KeyType e, TElemType value) {
    if (T == NULL) return ERROR;
    for (int i = 0; i < 100; i++) mem[i] = 0;
    to_mem(T);
    if (value.key != e && mem[value.key] == 1) {
        return ERROR;
    }
    BiTNode* node = LocateNode(T, e);
    mem[e] = 0;
    mem[value.key] = 1;
    if (node == NULL) return ERROR;
    node->data = value;
    return OK;
}

BiTNode* GetSibling(BiTree T, KeyType e) {
    if (T == NULL || (T->lchild == NULL && T->rchild == NULL)) return NULL;
    if (T->lchild && T->lchild->data.key == e) return T->rchild;
    if (T->rchild && T->rchild->data.key == e) return T->lchild;
    BiTNode* sibling = GetSibling(T->lchild, e);
    if (sibling) return sibling;
    return GetSibling(T->rchild, e);
}

status InsertNode(BiTree& T, KeyType e, int LR, TElemType c) {
    if (T == NULL) {
        if (LR == -1) {
            BiTNode* newNode = (BiTNode*)malloc(sizeof(BiTNode));
            if (!newNode) return OVERFLOW;
            newNode->data = c;
            newNode->lchild = newNode->rchild = NULL;
            T = newNode;
            return OK;
        }
        else {
            return ERROR;
        }
    }
    if (LR != 0 && LR != 1 && LR != -1) return ERROR;
    if (LocateNode(T, c.key) != NULL) return ERROR;
    if (LR == -1) {
        BiTNode* newNode = (BiTNode*)malloc(sizeof(BiTNode));
        if (!newNode) return OVERFLOW;
        newNode->data = c;
        newNode->rchild = T;
        newNode->lchild = NULL;
        T = newNode;
        return OK;
    }
    BiTNode* node = LocateNode(T, e);
    if (node == NULL) return ERROR;
    if (LR == 0) {
        BiTNode* newNode = (BiTNode*)malloc(sizeof(BiTNode));
        if (!newNode) return OVERFLOW;
        newNode->data = c;
        newNode->lchild = NULL;
        newNode->rchild = node->lchild;
        node->lchild = newNode;
        return OK;
    }
    else if (LR == 1) {
        BiTNode* newNode = (BiTNode*)malloc(sizeof(BiTNode));
        if (!newNode) return OVERFLOW;
        newNode->data = c;
        newNode->lchild = NULL;
        newNode->rchild = node->rchild;
        node->rchild = newNode;
        return OK;
    }
    else return ERROR;
    return ERROR;
}

status DeleteNode(BiTree& T, KeyType e) {
    if (T == NULL) return INFEASIBLE;
    if (T->data.key == e) {
        if (T->lchild == NULL && T->rchild == NULL) {
            free(T);
            T = NULL;
        }
        else if (T->lchild && T->rchild == NULL) {
            BiTNode* temp = T;
            T = T->lchild;
            free(temp);
        }
        else if (T->rchild && T->lchild == NULL) {
            BiTNode* temp = T;
            T = T->rchild;
            free(temp);
        }
        else {
            BiTNode* temp = T->lchild;
            while (temp->rchild) temp = temp->rchild;
            temp->rchild = T->rchild;
            BiTNode* toDelete = T;
            T = T->lchild;
            free(toDelete);
        }
        return OK;
    }
    if (DeleteNode(T->lchild, e) == OK) return OK;
    if (DeleteNode(T->rchild, e) == OK) return OK;
    return ERROR;
}

status PreOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    if (T) {
        visit(T);
        PreOrderTraverse(T->lchild, visit);
        PreOrderTraverse(T->rchild, visit);
    }
    return OK;
}

status InOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    BiTree stack[1000];
    int top = 0;
    stack[top++] = T;
    while (top) {
        T = stack[top - 1];
        while (T) {
            T = T->lchild;
            stack[top++] = T;
        }
        top--;
        if (top) {
            T = stack[--top];
            visit(T);
            stack[top++] = T->rchild;
        }
    }
    return OK;
}

status PostOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    if (T) {
        PostOrderTraverse(T->lchild, visit);
        PostOrderTraverse(T->rchild, visit);
        visit(T);
    }
    return OK;
}

status LevelOrderTraverse(BiTree T, void (*visit)(BiTree)) {
    BiTree Queue[1000];
    int front = 0, rear = 0;
    if (T) Queue[rear++] = T;
    while (front != rear) {
        T = Queue[front++];
        visit(T);
        if (T->lchild) Queue[rear++] = T->lchild;
        if (T->rchild) Queue[rear++] = T->rchild;
    }
    return OK;
}

int MaxPathSum(BiTree T) {
    if (T == NULL) return 0;
    if (T->lchild == NULL && T->rchild == NULL) return T->data.key;
    int left = MaxPathSum(T->lchild);
    int right = MaxPathSum(T->rchild);
    return (left > right ? left : right) + T->data.key;
}

BiTNode* LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2) {
    if (T == NULL) return NULL;
    if (T->data.key == e1 || T->data.key == e2) return T;
    BiTNode* left = LowestCommonAncestor(T->lchild, e1, e2);
    BiTNode* right = LowestCommonAncestor(T->rchild, e1, e2);
    if (left && right) return T;
    return left ? left : right;
}

void InvertTree(BiTree T) {
    if (T == NULL) return;
    BiTNode* tmp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = tmp;
    InvertTree(T->lchild);
    InvertTree(T->rchild);
}

void SaveTree(FILE* fp, BiTree T) {
    if (T == NULL) {
        int nullkey = -1;
        fwrite(&nullkey, sizeof(int), 1, fp);
        return;
    }
    fwrite(&T->data.key, sizeof(int), 1, fp);
    fwrite(T->data.others, sizeof(char), 20, fp);
    SaveTree(fp, T->lchild);
    SaveTree(fp, T->rchild);
}
status SaveBiTree(BiTree T, char FileName[])
{
    FILE* fp = fopen(FileName, "wb");
    if (!fp) return ERROR;
    SaveTree(fp, T);
    fclose(fp);
    return OK;
}

void LoadTree(FILE* fp, BiTree& T) {
    int key;
    if (fread(&key, sizeof(int), 1, fp) != 1) { T = NULL; return; }
    if (key == -1) { T = NULL; return; }
    T = (BiTNode*)malloc(sizeof(BiTNode));
    T->data.key = key;
    fread(T->data.others, sizeof(char), 20, fp);
    LoadTree(fp, T->lchild);
    LoadTree(fp, T->rchild);
}
status LoadBiTree(BiTree& T, char FileName[])
{
    FILE* fp = fopen(FileName, "rb");
    if (!fp) return ERROR;
    LoadTree(fp, T);
    fclose(fp);
    return OK;
}

int main() {
    TreeList treeList = { 0 };
    int current = -1;
    int op = 1;
    char tname[30];

    while (op) {
        system("cls");
        printf("\n\n");
        printf("      Menu for Binary Tree Structure \n");
        printf("-------------------------------------------------\n");
        printf(" 1. CreateBiTree      12. InOrderTraverse\n");
        printf(" 2. DestroyBiTree     13. PostOrderTraverse\n");
        printf(" 3. ClearBiTree       14. LevelOrderTraverse\n");
        printf(" 4. BiTreeEmpty       15. MaxPathSum\n");
        printf(" 5. BiTreeDepth       16. LowestCommonAncestor\n");
        printf(" 6. LocateNode        17. InvertTree\n");
        printf(" 7. Assign            18. SaveBiTree\n");
        printf(" 8. GetSibling        19. LoadBiTree\n");
        printf(" 9. InsertNode        20. AddTree\n");
        printf(" 10. DeleteNode       21. RemoveTree\n");
        printf(" 11. PreOrderTraverse 22. SwitchTree\n");
        printf(" 0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("请选择你的操作[0~22]:");
        scanf("%d", &op);

        switch (op) {
        case 1: { // 创建二叉树
            if (treeList.length >= MAX_TREES) {
                printf("树数量已达上限！\n"); getchar(); getchar(); break;
            }
            printf("请输入新二叉树名称：");
            scanf("%s", tname);
            for (int i = 0; i < treeList.length; ++i) {
                if (strcmp(treeList.trees[i].name, tname) == 0) {
                    printf("名称已存在！\n"); getchar(); getchar(); goto next;
                }
            }
            printf("请输入结点数：");
            int n; scanf("%d", &n);
            TElemType* defs = (TElemType*)malloc(sizeof(TElemType) * n);
            printf("请依次输入%d个结点的key和others（空结点key输入-1）：\n", n);
            for (int i = 0; i < n; ++i) {
                scanf("%d %s", &defs[i].key, defs[i].others);
            }
            BiTree T = NULL;
            if (CreateBiTree(T, defs) == OK) {
                strcpy(treeList.trees[treeList.length].name, tname);
                treeList.trees[treeList.length].T = T;
                current = treeList.length;
                treeList.length++;
                printf("创建成功！\n");
            }
            else {
                printf("创建失败（有重复key或内存不足）！\n");
            }
            free(defs);
            getchar(); getchar();
            break;
        }
        case 2: { // 销毁二叉树
            if (current == -1) { printf("请先切换到某棵树！\n"); getchar(); getchar(); break; }
            DestroyBiTree(treeList.trees[current].T);
            treeList.trees[current].T = NULL;
            printf("销毁成功！\n");
            getchar(); getchar();
            break;
        }
        case 3: { // 清空二叉树
            if (current == -1) { printf("请先切换到某棵树！\n"); getchar(); getchar(); break; }
            ClearBiTree(treeList.trees[current].T);
            printf("清空成功！\n");
            getchar(); getchar();
            break;
        }
        case 4: { // 判空
            if (current == -1) { printf("请先切换到某棵树！\n"); getchar(); getchar(); break; }
            printf(BiTreeEmpty(treeList.trees[current].T) ? "空树！\n" : "非空树！\n");
            getchar(); getchar();
            break;
        }
        case 5: { // 深度
            if (current == -1) { printf("请先切换到某棵树！\n"); getchar(); getchar(); break; }
            printf("树深度为：%d\n", BiTreeDepth(treeList.trees[current].T));
            getchar(); getchar();
            break;
        }
        case 6: { // 查找结点
            if (current == -1) { printf("请先切换到某棵树！\n"); getchar(); getchar(); break; }
            printf("请输入要查找的key：");
            int k; scanf("%d", &k);
            BiTNode* node = LocateNode(treeList.trees[current].T, k);
            if (node) printf("找到结点，others=%s\n", node->data.others);
            else printf("未找到！\n");
            getchar(); getchar();
            break;
        }
        case 7: { // 结点赋值
            if (current == -1) { printf("请先切换到某棵树！\n"); getchar(); getchar(); break; }
            printf("请输入要赋值的key：");
            int k; scanf("%d", &k);
            TElemType val;
            printf("请输入新key和others：");
            scanf("%d %s", &val.key, val.others);
            if (Assign(treeList.trees[current].T, k, val) == OK)
                printf("赋值成功！\n");
            else
                printf("赋值失败（重复key或未找到）！\n");
            getchar(); getchar();
            break;
        }
        case 8: { // 获得兄弟结点
            if (current == -1) { printf("请先切换到某棵树！\n"); getchar(); getchar(); break; }
            printf("请输入key：");
            int k; scanf("%d", &k);
            BiTNode* sib = GetSibling(treeList.trees[current].T, k);
            if (sib) printf("兄弟结点key=%d, others=%s\n", sib->data.key, sib->data.others);
            else printf("无兄弟结点！\n");
            getchar(); getchar();
            break;
        }
        case 9: { // 插入结点
            if (current == -1) { printf("请先切换到某棵树！\n"); getchar(); getchar(); break; }
            printf("请输入父结点key、LR(0左1右-1根)、新结点key和others：");
            int e, LR; TElemType c;
            scanf("%d %d %d %s", &e, &LR, &c.key, c.others);
            if (InsertNode(treeList.trees[current].T, e, LR, c) == OK)
                printf("插入成功！\n");
            else
                printf("插入失败！\n");
            getchar(); getchar();
            break;
        }
        case 10: { // 删除结点
            if (current == -1) { printf("请先切换到某棵树！\n"); getchar(); getchar(); break; }
            printf("请输入要删除的key：");
            int k; scanf("%d", &k);
            if (DeleteNode(treeList.trees[current].T, k) == OK)
                printf("删除成功！\n");
            else
                printf("删除失败！\n");
            getchar(); getchar();
            break;
        }
        case 11: { // 前序遍历
            if (current == -1) { printf("请先切换到某棵树！\n"); getchar(); getchar(); break; }
            printf("前序遍历：");
            PreOrderTraverse(treeList.trees[current].T, PrintNode);
            printf("\n");
            getchar(); getchar();
            break;
        }
        case 12: { // 中序遍历
            if (current == -1) { printf("请先切换到某棵树！\n"); getchar(); getchar(); break; }
            printf("中序遍历：");
            InOrderTraverse(treeList.trees[current].T, PrintNode);
            printf("\n");
            getchar(); getchar();
            break;
        }
        case 13: { // 后序遍历
            if (current == -1) { printf("请先切换到某棵树！\n"); getchar(); getchar(); break; }
            printf("后序遍历：");
            PostOrderTraverse(treeList.trees[current].T, PrintNode);
            printf("\n");
            getchar(); getchar();
            break;
        }
        case 14: { // 层序遍历
            if (current == -1) { printf("请先切换到某棵树！\n"); getchar(); getchar(); break; }
            printf("层序遍历：");
            LevelOrderTraverse(treeList.trees[current].T, PrintNode);
            printf("\n");
            getchar(); getchar();
            break;
        }
        case 15: { // 最大路径和
            if (current == -1) { printf("请先切换到某棵树！\n"); getchar(); getchar(); break; }
            printf("最大路径和为：%d\n", MaxPathSum(treeList.trees[current].T));
            getchar(); getchar();
            break;
        }
        case 16: { // 最近公共祖先
            if (current == -1) { printf("请先切换到某棵树！\n"); getchar(); getchar(); break; }
            printf("请输入两个结点的key：");
            int e1, e2; scanf("%d %d", &e1, &e2);
            BiTNode* lca = LowestCommonAncestor(treeList.trees[current].T, e1, e2);
            if (lca) printf("最近公共祖先key=%d, others=%s\n", lca->data.key, lca->data.others);
            else printf("未找到！\n");
            getchar(); getchar();
            break;
        }
        case 17: { // 翻转二叉树
            if (current == -1) { printf("请先切换到某棵树！\n"); getchar(); getchar(); break; }
            InvertTree(treeList.trees[current].T);
            printf("翻转完成！\n");
            getchar(); getchar();
            break;
        }
        case 18: { // 保存到文件
            if (current == -1) { printf("请先切换到某棵树！\n"); getchar(); getchar(); break; }
            char fname[100];
            printf("请输入保存文件名：");
            scanf("%s", fname);
            if (SaveBiTree(treeList.trees[current].T, fname) == OK)
                printf("保存成功！\n");
            else
                printf("保存失败！\n");
            getchar(); getchar();
            break;
        }
        case 19: { // 从文件加载
            if (treeList.length >= MAX_TREES) {
                printf("树数量已达上限！\n"); getchar(); getchar(); break;
            }
            char fname[100], tname2[30];
            printf("请输入加载后树的名称：");
            scanf("%s", tname2);
            for (int i = 0; i < treeList.length; ++i) {
                if (strcmp(treeList.trees[i].name, tname2) == 0) {
                    printf("名称已存在！\n"); getchar(); getchar(); goto next;
                }
            }
            printf("请输入文件名：");
            scanf("%s", fname);
            BiTree T = NULL;
            if (LoadBiTree(T, fname) == OK) {
                strcpy(treeList.trees[treeList.length].name, tname2);
                treeList.trees[treeList.length].T = T;
                current = treeList.length;
                treeList.length++;
                printf("加载成功！\n");
            }
            else {
                printf("加载失败！\n");
            }
            getchar(); getchar();
            break;
        }
        case 20: { // 添加树
            if (treeList.length >= MAX_TREES) {
                printf("树数量已达上限！\n"); getchar(); getchar(); break;
            }
            printf("请输入新二叉树名称：");
            scanf("%s", tname);
            for (int i = 0; i < treeList.length; ++i) {
                if (strcmp(treeList.trees[i].name, tname) == 0) {
                    printf("名称已存在！\n"); getchar(); getchar(); goto next;
                }
            }
            treeList.trees[treeList.length].T = NULL;
            strcpy(treeList.trees[treeList.length].name, tname);
            current = treeList.length;
            treeList.length++;
            printf("添加成功！\n");
            getchar(); getchar();
            break;
        }
        case 21: { // 移除树
            printf("请输入要移除的树名称：");
            scanf("%s", tname);
            int idx = -1;
            for (int i = 0; i < treeList.length; ++i) {
                if (strcmp(treeList.trees[i].name, tname) == 0) { idx = i; break; }
            }
            if (idx == -1) { printf("未找到！\n"); getchar(); getchar(); break; }
            DestroyBiTree(treeList.trees[idx].T);
            for (int j = idx; j < treeList.length - 1; ++j)
                treeList.trees[j] = treeList.trees[j + 1];
            treeList.length--;
            if (current == idx) current = -1;
            printf("移除成功！\n");
            getchar(); getchar();
            break;
        }
        case 22: { // 切换树
            printf("请输入要切换的树名称：");
            scanf("%s", tname);
            int idx = -1;
            for (int i = 0; i < treeList.length; ++i) {
                if (strcmp(treeList.trees[i].name, tname) == 0) { idx = i; break; }
            }
            if (idx == -1) { printf("未找到！\n"); getchar(); getchar(); break; }
            current = idx;
            printf("已切换到：%s\n", treeList.trees[current].name);
            getchar(); getchar();
            break;
        }
        case 0:
            break;
        }
    next:;
    }
    printf("欢迎下次再使用本系统！\n");
    return 0;
}