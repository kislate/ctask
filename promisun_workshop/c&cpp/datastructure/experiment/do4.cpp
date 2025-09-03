#include "stdio.h"
#include "stdlib.h"
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20

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
    printf("%d ", G.vertices[v].data.key);  
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
                    printf("%d ", G.vertices[p->adjvex].data.key,G.vertices[i].data.others); 
                }
                p = p->nextarc; 
            }
        }
    }
    /********** End **********/
}

status Save(ALGraph G, char FileName[], ArcNode *p, FILE *fp, int i)
{
    // 递归保存
    if(p == NULL) return OK;
    Save(G, FileName, p->nextarc, fp, i);
    fprintf(fp, "%d %d\n", i, p->adjvex);
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
    /********** End 2 **********/
}
