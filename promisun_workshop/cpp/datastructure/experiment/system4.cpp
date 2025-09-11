#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include <windows.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
#define MAX_GRAPHS 10

typedef int status;
typedef int KeyType; 
typedef enum {DG,DN,UDG,UDN} GraphKind;//DG有向图，DN有向网，UDG无向图，UDN无向网
typedef struct {
    KeyType  key;
    char others[20];
} VertexType; //顶点类型定义

typedef struct ArcNode {         //表结点类型定义
    int adjvex;              //顶点位置编号 
    struct ArcNode  *nextarc;	   //下一个表结点指针
} ArcNode;

typedef struct VNode{				//头结点及其数组类型定义
    VertexType data;       	//顶点信息
    ArcNode *firstarc;      	 //指向第一条弧
} VNode,AdjList[MAX_VERTEX_NUM];

typedef  struct {  //邻接表的类型定义
    AdjList vertices;     	 //头结点数组
    int vexnum,arcnum;   	  //顶点数、弧数
    GraphKind  kind;        //图的类型
} ALGraph;

// 多图管理结构体
typedef struct {
    char name[30];
    ALGraph G;
} GraphEntry;

typedef struct {
    GraphEntry graphs[MAX_GRAPHS];
    int length;
} GraphList;

// 函数声明（do4.cpp原函数）
status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2]);
status DestroyGraph(ALGraph &G);
int LocateVex(ALGraph G, KeyType u);
status PutVex(ALGraph &G, KeyType u, VertexType value);
int FirstAdjVex(ALGraph G, KeyType u);
int NextAdjVex(ALGraph G, KeyType v, KeyType w);
status InsertVex(ALGraph &G, VertexType v);
status DeleteVex(ALGraph &G, KeyType v);
status InsertArc(ALGraph &G, KeyType v, KeyType w);
status DeleteArc(ALGraph &G, KeyType v, KeyType w);
status DFSTraverse(ALGraph &G, void (*visit)(VertexType));
status BFSTraverse(ALGraph &G, void (*visit)(VertexType));
status Save(ALGraph G, char FileName[], ArcNode *p, FILE *fp, int i);
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);
void DFS(ALGraph G, int v, int visited[]) ;
status to_mem(VertexType V[],KeyType VR[][2], int mem[]);


// 附加功能1：输出与v距离小于k的所有顶点
void VerticesSetLessThanK(ALGraph &G, KeyType v, int k) {
    int idx = LocateVex(G, v);
    if(idx == -1) {
        printf("未找到起点！\n");
        return;
    }
    int dist[MAX_VERTEX_NUM];
    for(int i=0;i<MAX_VERTEX_NUM;i++) dist[i]=-1;
    dist[idx]=0;
    int queue[MAX_VERTEX_NUM], front=0, rear=0;
    queue[rear++] = idx;
    while(front < rear) {
        int u = queue[front++];
        ArcNode *p = G.vertices[u].firstarc;
        while(p) {
            if(dist[p->adjvex]==-1) {
                dist[p->adjvex]=dist[u]+1;
                queue[rear++]=p->adjvex;
            }
            p=p->nextarc;
        }
    }
    printf("与%d距离小于%d的顶点有：", v, k);
    int found = 0;
    for(int i=0;i<G.vexnum;i++) {
        if(dist[i]!=-1 && dist[i]<k && i!=idx) {
            printf("%d(%s) ", G.vertices[i].data.key, G.vertices[i].data.others);
            found = 1;
        }
    }
    if(!found) printf("无");
    printf("\n");
}

// 附加功能2：最短路径长度（BFS）
int ShortestPathLength(ALGraph &G, KeyType v, KeyType w) {
    int idx1 = LocateVex(G, v);
    int idx2 = LocateVex(G, w);
    if(idx1 == -1 || idx2 == -1) return -1;
    int dist[MAX_VERTEX_NUM];
    for(int i=0;i<MAX_VERTEX_NUM;i++) dist[i]=-1;
    dist[idx1]=0;
    int queue[MAX_VERTEX_NUM], front=0, rear=0;
    queue[rear++] = idx1;
    while(front < rear) {
        int u = queue[front++];
        if(u == idx2) return dist[u];
        ArcNode *p = G.vertices[u].firstarc;
        while(p) {
            if(dist[p->adjvex]==-1) {
                dist[p->adjvex]=dist[u]+1;
                queue[rear++]=p->adjvex;
            }
            p=p->nextarc;
        }
    }
    return -1;
}

// 附加功能3：连通分量个数
void dfs(ALGraph &G, int v, int visited[]) {
        visited[v]=1;
        ArcNode *p = G.vertices[v].firstarc;
        while(p) {
            if(!visited[p->adjvex]) dfs(G, p->adjvex, visited);
            p=p->nextarc;
        }
}
int ConnectedComponentsNums(ALGraph &G) {
    int visited[MAX_VERTEX_NUM]={0};
    int cnt=0;
    
    for(int i=0;i<G.vexnum;i++) {
        if(!visited[i]) {
            cnt++;
            dfs(G, i, visited);
        }
    }
    return cnt;
}

// ========== 多图管理主程序 ==========

void SingleGraphMenu(ALGraph &G, char name[]);

int main() {
    system("chcp 65001 > nul"); // 设置控制台编码为UTF-8
    printf("欢迎使用图管理系统！\n");
    int op = 1;
    char name[30];
    GraphList glist;
    glist.length = 0;

    while (op) {
        system("cls");
        printf("\n\n");
        printf("      Menu for Graph Management System\n");
        printf("-----------------------------------------------------\n");
        printf("        1. AddGraph           4. SingleGraph\n");
        printf("        2. RemoveGraph        5. GraphsTraverse(DFS)\n");
        printf("        3. LocateGraph        0. Exit\n");
        printf("-----------------------------------------------------\n");
        printf("    请选择你的操作[0~5]:");
        scanf("%d", &op);
        switch (op) {
            case 1: { // AddGraph
                printf("请输入图名称：\n");
                scanf("%s", name);
                if (glist.length >= MAX_GRAPHS) {
                    printf("空间已满，无法再创建图！\n");
                    getchar(); getchar();
                    break;
                }
                int name_exists = 0;
                for (int i = 0; i < glist.length; i++) {
                    if (strcmp(glist.graphs[i].name, name) == 0) {
                        printf("图名称已存在！\n");
                        getchar(); getchar();
                        name_exists = 1;
                        break;
                    }
                }
                if (!name_exists) {
                    VertexType V[MAX_VERTEX_NUM+1];
                    KeyType VR[MAX_VERTEX_NUM*MAX_VERTEX_NUM][2];
                    int vcnt = 0, ecnt = 0;
                    printf("请输入顶点信息（key others），以-1 结束：\n");
                    while (1) {
                        scanf("%d", &V[vcnt].key);
                        if (V[vcnt].key == -1) break;
                        scanf("%s", V[vcnt].others);
                        vcnt++;
                    }
                    V[vcnt].key = -1; // 结束标记
                    printf("请输入边信息（key1 key2），以-1 -1 结束：\n");
                    while (1) {
                        scanf("%d%d", &VR[ecnt][0], &VR[ecnt][1]);
                        if (VR[ecnt][0] == -1 && VR[ecnt][1] == -1) break;
                        ecnt++;
                    }
                    VR[ecnt][0] = VR[ecnt][1] = -1;
                    if (CreateCraph(glist.graphs[glist.length].G, V, VR) == OK) {
                        strcpy(glist.graphs[glist.length].name, name);
                        glist.length++;
                        printf("图创建成功！\n");
                    } else {
                        printf("图创建失败！\n");
                    }
                    getchar(); getchar();
                }
                break;
            }
            case 2: { // RemoveGraph
                printf("请输入要删除的图名称：\n");
                scanf("%s", name);
                int found = 0;
                for (int i = 0; i < glist.length; i++) {
                    if (strcmp(glist.graphs[i].name, name) == 0) {
                        DestroyGraph(glist.graphs[i].G);
                        for (int j = i; j < glist.length - 1; j++)
                            glist.graphs[j] = glist.graphs[j + 1];
                        glist.length--;
                        printf("该图删除成功！\n");
                        found = 1;
                        break;
                    }
                }
                if (!found) printf("未找到该图，无法删除！\n");
                getchar(); getchar();
                break;
            }
            case 3: { // LocateGraph
                printf("请输入要查找的图名称：\n");
                scanf("%s", name);
                int found = 0;
                for (int i = 0; i < glist.length; i++) {
                    if (strcmp(glist.graphs[i].name, name) == 0) {
                        printf("图 %s 的逻辑序号为：%d\n", name, i + 1);
                        found = 1;
                        break;
                    }
                }
                if (!found) printf("未找到该图！\n");
                getchar(); getchar();
                break;
            }
            case 4: { // SingleGraph
                printf("对哪一个图展开更多单一操作（输入逻辑编号即可）？\n");
                int idx2;
                scanf("%d", &idx2);
                if (idx2 < 1 || idx2 > glist.length) {
                    printf("输入的逻辑编号不合法！\n");
                    getchar(); getchar();
                    break;
                }
                SingleGraphMenu(glist.graphs[idx2 - 1].G, glist.graphs[idx2 - 1].name);
                break;
            }
            case 5: { // GraphsTraverse(DFS)
                for (int i = 0; i < glist.length; i++) {
                    printf("%s: ", glist.graphs[i].name);
                    DFSTraverse(glist.graphs[i].G, NULL); // 可自定义visit函数
                    printf("\n");
                }
                getchar(); getchar();
                break;
            }
            case 0:
                break;
        }
    }
    printf("欢迎下次再使用本系统！\n");
    return 0;
}

// 单图操作菜单
void SingleGraphMenu(ALGraph &G, char name[]) {
    int op = 1;
    while (op) {
        system("cls");
        printf("\n\n");
        printf("      Menu for Single Graph [%s]\n", name);
        printf("-----------------------------------------------------\n");
        printf("   1. DFSTraverse         7. DeleteVex\n");
        printf("   2. BFSTraverse         8. DeleteArc\n");
        printf("   3. InsertVex           9. DestroyGraph\n");
        printf("   4. InsertArc           10. LocateVex\n");
        printf("   5. SaveGraph           11. PutVex\n");
        printf("   6. LoadGraph           12. FirstAdjVex\n");
        printf("   13. NextAdjVex         14. VerticesSetLessThanK\n");
        printf("   15. ShortestPathLength 16. ConnectedComponentsNums\n");
        printf("   0. Exit\n");
        printf("-----------------------------------------------------\n");
        printf("请选择你的操作[0~16]:");
        scanf("%d", &op);
        switch (op) {
            case 1:
                DFSTraverse(G, NULL); // 可自定义visit
                printf("\n"); getchar(); getchar();
                break;
            case 2:
                BFSTraverse(G, NULL); // 可自定义visit
                printf("\n"); getchar(); getchar();
                break;
            case 3: { // InsertVex
                VertexType v;
                printf("请输入顶点key和others：");
                scanf("%d%s", &v.key, v.others);
                if (InsertVex(G, v) == OK)
                    printf("插入顶点成功！\n");
                else
                    printf("插入顶点失败！\n");
                getchar(); getchar();
                break;
            }
            case 4: { // InsertArc
                int v, w;
                printf("请输入边的两个顶点key：");
                scanf("%d%d", &v, &w);
                if (InsertArc(G, v, w) == OK)
                    printf("插入边成功！\n");
                else
                    printf("插入边失败！\n");
                getchar(); getchar();
                break;
            }
            case 5: { // SaveGraph
                char fname[100];
                printf("请输入文件名：");
                scanf("%s", fname);
                if (SaveGraph(G, fname) == OK)
                    printf("保存成功！\n");
                else
                    printf("保存失败！\n");
                getchar(); getchar();
                break;
            }
            case 6: { // LoadGraph
                char fname[100];
                printf("请输入文件名：");
                scanf("%s", fname);
                if (LoadGraph(G, fname) == OK)
                    printf("读取成功！\n");
                else
                    printf("读取失败！\n");
                getchar(); getchar();
                break;
            }
            case 7: { // DeleteVex
                int v;
                printf("请输入要删除的顶点key：");
                scanf("%d", &v);
                if (DeleteVex(G, v) == OK)
                    printf("删除顶点成功！\n");
                else
                    printf("删除顶点失败！\n");
                getchar(); getchar();
                break;
            }
            case 8: { // DeleteArc
                int v, w;
                printf("请输入要删除的边的两个顶点key：");
                scanf("%d%d", &v, &w);
                if (DeleteArc(G, v, w) == OK)
                    printf("删除边成功！\n");
                else
                    printf("删除边失败！\n");
                getchar(); getchar();
                break;
            }
            case 9: { // DestroyGraph
                if (DestroyGraph(G) == OK)
                    printf("图已销毁！\n");
                else
                    printf("销毁失败！\n");
                getchar(); getchar();
                break;
            }
            case 10: { // LocateVex
                int v;
                printf("请输入要查找的顶点key：");
                scanf("%d", &v);
                int idx = LocateVex(G, v);
                if (idx != -1)
                    printf("顶点逻辑序号为：%d\n", idx + 1);
                else
                    printf("未找到该顶点！\n");
                getchar(); getchar();
                break;
            }
            case 11: { // PutVex
                int v;
                VertexType value;
                printf("请输入要修改的顶点key：");
                scanf("%d", &v);
                printf("请输入新顶点key和others：");
                scanf("%d%s", &value.key, value.others);
                if (PutVex(G, v, value) == OK)
                    printf("修改成功！\n");
                else
                    printf("修改失败！\n");
                getchar(); getchar();
                break;
            }
            case 12: { // FirstAdjVex
                int v;
                printf("请输入顶点key：");
                scanf("%d", &v);
                int idx = FirstAdjVex(G, v);
                if (idx != -1)
                    printf("第一邻接顶点逻辑序号为：%d\n", idx + 1);
                else
                    printf("未找到邻接顶点！\n");
                getchar(); getchar();
                break;
            }
            case 13: { // NextAdjVex
                int v, w;
                printf("请输入顶点key和其邻接顶点key：");
                scanf("%d%d", &v, &w);
                int idx = NextAdjVex(G, v, w);
                if (idx != -1)
                    printf("下一个邻接顶点逻辑序号为：%d\n", idx + 1);
                else
                    printf("未找到下一个邻接顶点！\n");
                getchar(); getchar();
                break;
            }
            case 14: { // VerticesSetLessThanK
                int v, k;
                printf("请输入起点key和距离k：");
                scanf("%d%d", &v, &k);
                VerticesSetLessThanK(G, v, k);
                getchar(); getchar();
                break;
            }
            case 15: { // ShortestPathLength
                int v, w;
                printf("请输入起点key和终点key：");
                scanf("%d%d", &v, &w);
                int len = ShortestPathLength(G, v, w);
                if(len == -1)
                    printf("不可达！\n");
                else
                    printf("最短路径长度为：%d\n", len);
                getchar(); getchar();
                break;
            }
            case 16: { // ConnectedComponentsNums
                int cnt = ConnectedComponentsNums(G);
                printf("连通分量个数为：%d\n", cnt);
                getchar(); getchar();
                break;
            }
            case 0:
                break;
        }
    }
}

//辅助函数：记忆顶点的关键字
status to_mem(VertexType V[],KeyType VR[][2], int mem[])
{
    int i=0,j=0;
    while(V[i].key != -1 && i < MAX_VERTEX_NUM) 
    {
        if(V[i].key <= 0 ) return ERROR;
        mem[V[i].key] ++;
        if(mem[V[i].key] > 1) return ERROR;
        i++;
    }
    while(VR[j][0] != -1 && VR[j][1] != -1 )
    {
        if(VR[j][0] <= 0 || VR[j][1] <= 0) return ERROR;
        if(mem[VR[j][0]]==0 || mem[VR[j][1]] ==0 ) return ERROR;
        j++;
    }
    return OK;
}

int FindIndex(VertexType V[], int key) {
    for(int i=0; V[i].key!=-1 && i<MAX_VERTEX_NUM; i++) { 
        if(V[i].key == key) return i;
    }
    return -1;
}

status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
{
    int mem[100] = {0};
    if(to_mem(V, VR, mem) == ERROR) return ERROR;
    G.vexnum = 0;
    G.arcnum = 0;
    G.kind = UDG;
    int i=0,j=0;
    while(V[i].key != -1 && i < MAX_VERTEX_NUM)
    {
        G.vexnum++;
        G.vertices[i].data = V[i];
        G.vertices[i].firstarc = NULL;
        i++;
    }
    if(i == 0 || V[i].key!=-1) return ERROR; 
    while(VR[j][0] != -1 && VR[j][1] != -1 ) 
    {
        int from = FindIndex(V, VR[j][0]);
        int to = FindIndex(V, VR[j][1]);
        if(from == -1 || to == -1) return ERROR;
        G.arcnum++;
        ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = to;
        p->nextarc = G.vertices[from].firstarc;
        G.vertices[from].firstarc = p;

        if(G.kind == UDG) {
            ArcNode *q = (ArcNode *)malloc(sizeof(ArcNode));
            q->adjvex = from;
            q->nextarc = G.vertices[to].firstarc;
            G.vertices[to].firstarc = q;
        }
        j++;
    }
    return OK;
}

//销毁无向图G
status DestroyGraph(ALGraph &G)
/*删除G的全部顶点和边*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for(int i = 0; i < G.vexnum; i++) {
        ArcNode *p = G.vertices[i].firstarc;
        while(p != NULL) {
            ArcNode *temp = p;
            p = p->nextarc;
            free(temp);
        }
        G.vertices[i].firstarc = NULL; //清空弧表
        G.vertices[i].data.key = 0; //清空顶点数据
        G.vertices[i].data.others[0] = '\0'; 
    }
    G.vexnum=0;G.arcnum=0;
    return OK;
    /********** End **********/
}

int LocateVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for(int i = 0; i < G.vexnum; i++) {
        if(G.vertices[i].data.key == u) {
            return i; 
        }
    }
    return -1;
    /********** End **********/
}

status PutVex(ALGraph &G,KeyType u,VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int j = -1;
    for(int i=0 ; i < G.vexnum; i++) {
        if(G.vertices[i].data.key == u) j=i;
            if(G.vertices[i].data.key == value.key) 
                if(G.vertices[i].data.key != u) return ERROR;
    }
    if(j == -1) return ERROR;
    G.vertices[j].data = value; //修改顶点值
    return OK;
    /********** End **********/
}

int FirstAdjVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i=LocateVex(G, u); 
    if(i == -1) return -1; 
    ArcNode *p = G.vertices[i].firstarc;
    if(p == NULL) return -1; 
    return p->adjvex; 
    /********** End **********/
}

int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//v对应G的一个顶点,w对应v的邻接顶点；操作结果是返回v的（相对于w）下一个邻接顶点的位序；如果w是最后一个邻接顶点，或v、w对应顶点不存在，则返回-1。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i = LocateVex(G, v);
    int j = LocateVex(G, w);
    if(i == -1 || j == -1) return -1;
    ArcNode *p = G.vertices[i].firstarc;
    while(p != NULL) {
        if(p->adjvex == j) { //找到w
            if(p->nextarc != NULL) return p->nextarc->adjvex; //返回下一个邻接顶点
            else return -1; //没有下一个邻接顶点
        }
        p = p->nextarc; //继续查找
    }
    return -1; 
    /********** End **********/
}

status InsertVex(ALGraph &G,VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(G.vexnum >= MAX_VERTEX_NUM){
        return ERROR;
    }
    if(LocateVex(G, v.key) != -1){
        return ERROR;
    }
    G.vertices[G.vexnum].data = v;
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum++;
    return OK;
    /********** End **********/
}

status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(G.vexnum == 1 && G.arcnum == 0) return ERROR;
    int pos = LocateVex(G, v);
    if(pos == -1) return ERROR;
    ArcNode *p = G.vertices[pos].firstarc;
    while(p){
        ArcNode *q = p;
        p = p->nextarc;
        free(q);
        G.arcnum--;
    }
    for(int i = 0; i < G.vexnum; i++){
        if(i == pos) continue;
        ArcNode *arc = G.vertices[i].firstarc;
        ArcNode *prev = NULL;
        int found = 0;
        while(arc){
            ArcNode *next = arc->nextarc;
            if(arc->adjvex == pos){
                found = 1;
                if(prev){
                    prev->nextarc = next;
                    free(arc);
                }
                else{
                    G.vertices[i].firstarc = next;
                    free(arc);
                }
            }
            if(arc->adjvex > pos) arc->adjvex--;
            if(!found)
            {
                prev = arc;
                arc = arc->nextarc;
            }
            else{
                arc = next;
            }
        }
    }
    for(int i = pos; i < G.vexnum - 1; i++){
        G.vertices[i] = G.vertices[i + 1];
    }
    G.vexnum--;
    return OK;
    /********** End **********/
}

status InsertArc(ALGraph &G,KeyType v,KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int pos1 = LocateVex(G, v);
    int pos2 = LocateVex(G, w);
    if(pos1 == -1 || pos2 == -1) return ERROR;
    ArcNode *check = G.vertices[pos1].firstarc;
    while(check){
        if(check->adjvex == pos2) return ERROR;
        check = check->nextarc;
    }
    ArcNode *arc = (ArcNode *)malloc(sizeof(ArcNode));
    arc->adjvex = pos2;
    arc->nextarc = G.vertices[pos1].firstarc;
    G.vertices[pos1].firstarc = arc;
    G.kind = UDG;
    if(G.kind == UDG || G.kind == UDN){
        ArcNode *arc2 = (ArcNode *)malloc(sizeof(ArcNode));
        arc2->adjvex = pos1;
        arc2->nextarc = G.vertices[pos2].firstarc;
        G.vertices[pos2].firstarc = arc2;
    }
    G.arcnum++;
    return OK;
    /********** End **********/
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int pos1 = LocateVex(G, v);
    int pos2 = LocateVex(G, w);
    if(pos1 == -1 || pos2 == -1) return ERROR;
    ArcNode *arc = G.vertices[pos1].firstarc;
    ArcNode *prev = NULL;
    while(arc){
        if(arc->adjvex == pos2){
            if(prev){
                prev->nextarc = arc->nextarc;
                free(arc);
            }
            else{
                G.vertices[pos1].firstarc = arc->nextarc;
                free(arc);
            }
            G.arcnum--;
            break;
        }
        prev = arc;
        arc = arc->nextarc;
    }
    arc = G.vertices[pos2].firstarc;
    prev = NULL;
    while(arc){
        if(arc->adjvex == pos1){
            if(prev){
                prev->nextarc = arc->nextarc;
                free(arc);
            }
            else{
                G.vertices[pos2].firstarc = arc->nextarc;
                free(arc);
            }
            break;
        }
        prev = arc;
        arc = arc->nextarc;
    }
    return OK;
    /********** End **********/
}

void DFS(ALGraph G, int v, int visited[]) {
    visited[v] = 1; 
    printf("%d %s ", G.vertices[v].data.key,G.vertices[v].data.others);  
    ArcNode *p = G.vertices[v].firstarc;
    while(p != NULL) {
        if(!visited[p->adjvex]) { 
            DFS(G, p->adjvex, visited); 
        }
        p = p->nextarc; 
    }
}
status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int visited[MAX_VERTEX_NUM] = {0}; 
    for(int i = 0; i < G.vexnum; i++) {
        if(!visited[i]) {
            DFS(G,i,visited); 
        }
    }
    return OK;
    /********** End **********/
}

status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int visited[MAX_VERTEX_NUM] = {0};
    for(int i = 0; i < G.vexnum; i++) {
        if(!visited[i]) {
            visited[i] = 1; 
            printf("%d %s ", G.vertices[i].data.key,G.vertices[i].data.others); 
            ArcNode *p = G.vertices[i].firstarc;
            while(p != NULL) {
                if(!visited[p->adjvex]) {
                    visited[p->adjvex] = 1; 
                    printf("%d %s ", G.vertices[p->adjvex].data.key,G.vertices[p->adjvex].data.others); 
                }
                p = p->nextarc; 
            }
        }
    }
    return OK;
    /********** End **********/
}

status Save(ALGraph G, char FileName[], ArcNode *p, FILE *fp, int i)
{
    // 递归保存
    if(p == NULL) return OK;
    Save(G, FileName, p->nextarc, fp, i);
    fprintf(fp, "%d %d\n", i, p->adjvex);
    return OK;
}
status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    FILE *fp = fopen(FileName, "w");
    fprintf(fp, "%d %d %d\n", G.vexnum, G.arcnum, G.kind);
    for(int i = 0; i < G.vexnum; i++) {
        fprintf(fp, "%d %s\n", G.vertices[i].data.key, G.vertices[i].data.others);
    }
    for(int i = 0; i < G.vexnum; i++) {
        ArcNode *p = G.vertices[i].firstarc;
        Save(G, FileName, p, fp, i);
    }
    fclose(fp);
    return OK;
    /********** End 1 **********/
}
status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    FILE *fp = fopen(FileName, "r");
    fscanf(fp, "%d%d%d", &G.vexnum, &G.arcnum, (int*)&G.kind);
    for(int i = 0; i < G.vexnum; i++) {
        fscanf(fp, "%d%s", &G.vertices[i].data.key, G.vertices[i].data.others);
        G.vertices[i].firstarc = NULL;
    }
    int u, v;
    while(fscanf(fp, "%d%d", &u, &v) == 2) {
        // 插入邻接表两端
        ArcNode *arc1 = (ArcNode*)malloc(sizeof(ArcNode));
        arc1->adjvex = v;
        arc1->nextarc = G.vertices[u].firstarc;
        G.vertices[u].firstarc = arc1;
    }
    fclose(fp); 
    return OK;
    /********** End 2 **********/
}
