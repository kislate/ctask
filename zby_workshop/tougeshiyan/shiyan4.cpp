#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GRAPHS 10
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
typedef int status;
typedef int KeyType; 
typedef enum {DG,DN,UDG,UDN} GraphKind;
typedef struct {
     KeyType  key;
     char others[20];
} VertexType;
typedef struct ArcNode {
	 int adjvex;
     struct ArcNode  *nextarc;
} ArcNode;
typedef struct VNode{
   	VertexType data;
    ArcNode *firstarc;
    } VNode,AdjList[MAX_VERTEX_NUM];
typedef  struct {
    AdjList vertices;
    int vexnum,arcnum;
    GraphKind  kind;
} ALGraph;
typedef struct {
    char name[30];
    ALGraph G;
} NamedGraph;

typedef struct {
    NamedGraph graphs[MAX_GRAPHS];
    int length;
} GraphList;

void PrintVertex(VertexType v) {
    printf("%d %s ", v.key, v.others);
}

int flag[10000];

int check(VertexType V[], KeyType VR[][2]) {
    int k = 0;
    while (V[k].key != -1) {
        if (!flag[V[k].key]) {
            flag[V[k].key]++;
        } else
            return 0;
        k++;
    }
    if (k == 0 || k > MAX_VERTEX_NUM)
        return 0;
    k = 0;
    while (VR[k][0] != -1) {
        if (VR[k][0] == VR[k][1])
            return 0;
        if (flag[VR[k][1]] && flag[VR[k][0]]);
        else
            return 0;
        k++;
    }
    return 1;
}
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
{
    if (!check(V, VR))
        return ERROR;
    int k = 0;
    G.arcnum = G.vexnum = 0;
    while (V[k].key != -1) {
        G.vexnum++;
        G.vertices[k].data.key = V[k].key;
        strcpy(G.vertices[k].data.others, V[k].others);
        G.vertices[k].firstarc = NULL;
        k++;
    }
    k = 0;
    while (VR[k][0] != -1) {
        int pos = 0;
        int pos1 = 0, pos2 = 0;
        while (G.vertices[pos1].data.key != VR[k][0])
            pos1++;
        while (G.vertices[pos2].data.key != VR[k][1])
            pos2++;
        ArcNode* tmp1 = (ArcNode*)malloc(sizeof(ArcNode));
        ArcNode* tmp2 = (ArcNode*)malloc(sizeof(ArcNode));
        tmp1->adjvex = pos1;
        tmp2->adjvex = pos2;
        tmp1->nextarc = G.vertices[pos2].firstarc;
        tmp2->nextarc = G.vertices[pos1].firstarc;
        G.vertices[pos2].firstarc = tmp1;
        G.vertices[pos1].firstarc = tmp2;
        G.arcnum++;
        k++;
    }
    G.kind = UDG;
    return OK;
}

status DestroyGraph(ALGraph &G)
{
    for (int i = 0; i < G.vexnum; ++i) {
        ArcNode *current = G.vertices[i].firstarc;
        while (current != NULL) {
            ArcNode *temp = current;
            current = current->nextarc;
            free(temp);
        }
        G.vertices[i].firstarc = NULL;
    }
    G.vexnum = 0;
    G.arcnum = 0;
    return OK;
}

int LocateVex(ALGraph G,KeyType u)
{
    for (int i = 0; i < G.vexnum; ++i) {
        if (G.vertices[i].data.key == u) {
            return i;
        }
    }
    return -1;
}

status PutVex(ALGraph &G,KeyType u,VertexType value)
{
    for (int i = 0; i < G.vexnum; ++i) {
        if (G.vertices[i].data.key == value.key && G.vertices[i].data.key != u) {
            return ERROR;
        }
    }
    int pos = LocateVex(G, u);
    if (pos == -1) {
        return ERROR;
    }
    G.vertices[pos].data = value;
    return OK;
}

int FirstAdjVex(ALGraph G,KeyType u)
{
    int pos = LocateVex(G, u);
    if (pos == -1) {
        return -1;
    }
    ArcNode *firstArc = G.vertices[pos].firstarc;
    if (firstArc != NULL) {
        return firstArc->adjvex;
    } else {
        return -1;
    }
}

int NextAdjVex(ALGraph G,KeyType v,KeyType w)
{
    int vIndex = LocateVex(G, v);
    int wIndex = LocateVex(G, w);
    if (vIndex == -1 || wIndex == -1) {
        return -1;
    }
    ArcNode *arc = G.vertices[vIndex].firstarc;
    while (arc != NULL) {
        if (arc->adjvex == wIndex) {
            if (arc->nextarc != NULL) {
                return arc->nextarc->adjvex;
            } else {
                return -1;
            }
        }
        arc = arc->nextarc;
    }
    return -1;
}

status InsertVex(ALGraph &G,VertexType v)
{
    if (G.vexnum >= MAX_VERTEX_NUM) {
        return ERROR;
    }
    for (int i = 0; i < G.vexnum; ++i) {
        if (G.vertices[i].data.key == v.key) {
            return ERROR;
        }
    }
    G.vertices[G.vexnum].data = v;
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum++;
    return OK;
}

status DeleteVex(ALGraph &G,KeyType v)
{
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
}

status InsertArc(ALGraph &G,KeyType v,KeyType w)
{
    int vIndex = LocateVex(G, v);
    int wIndex = LocateVex(G, w);
    if (vIndex == -1 || wIndex == -1) {
        return ERROR;
    }
    ArcNode *arc = G.vertices[vIndex].firstarc;
    while (arc != NULL) {
        if (arc->adjvex == wIndex) {
            return ERROR;
        }
        arc = arc->nextarc;
    }
    ArcNode *arcVW = (ArcNode *)malloc(sizeof(ArcNode));
    if (!arcVW) return OVERFLOW;
    arcVW->adjvex = wIndex;
    arcVW->nextarc = G.vertices[vIndex].firstarc;
    G.vertices[vIndex].firstarc = arcVW;
    ArcNode *arcWW = (ArcNode *)malloc(sizeof(ArcNode));
    if (!arcWW) return OVERFLOW;
    arcWW->adjvex = vIndex;
    arcWW->nextarc = G.vertices[wIndex].firstarc;
    G.vertices[wIndex].firstarc = arcWW;
    G.arcnum++;
    return OK;
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
{
    int vIndex = LocateVex(G, v);
    int wIndex = LocateVex(G, w);
    if (vIndex == -1 || wIndex == -1) {
        return ERROR;
    }
    ArcNode *prev = NULL;
    ArcNode *curr = G.vertices[vIndex].firstarc;
    while (curr != NULL && curr->adjvex != wIndex) {
        prev = curr;
        curr = curr->nextarc;
    }
    if (curr == NULL) {
        return ERROR;
    }
    if (prev == NULL) {
        G.vertices[vIndex].firstarc = curr->nextarc;
    } else {
        prev->nextarc = curr->nextarc;
    }
    free(curr);
    prev = NULL;
    curr = G.vertices[wIndex].firstarc;
    while (curr != NULL && curr->adjvex != vIndex) {
        prev = curr;
        curr = curr->nextarc;
    }
    if (curr == NULL) {
        return ERROR;
    }
    if (prev == NULL) {
        G.vertices[wIndex].firstarc = curr->nextarc;
    } else {
        prev->nextarc = curr->nextarc;
    }
    free(curr);
    G.arcnum--;
    return OK;
}

void DFS(ALGraph G, int v, int visited[], void (*visit)(VertexType)) {
    visited[v] = 1;
    visit(G.vertices[v].data);
    ArcNode *p = G.vertices[v].firstarc;
    while (p != NULL) {
        int w = p->adjvex;
        if (!visited[w]) {
            DFS(G, w, visited, visit);
        }
        p = p->nextarc;
    }
}
status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
{
    if (visit == NULL) return ERROR;
    int visited[MAX_VERTEX_NUM] = {0};
    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i]) {
            DFS(G, i, visited, visit);
        }
    }
    return OK;
}

status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
{
    if (visit == NULL) return ERROR;
    int visited[MAX_VERTEX_NUM] = {0};
    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i]) {
            int queue[MAX_VERTEX_NUM], front = 0, rear = 0;
            queue[rear++] = i;
            visited[i] = 1;
            while (front != rear) {
                int v = queue[front++];
                visit(G.vertices[v].data);
                ArcNode *p = G.vertices[v].firstarc;
                while (p != NULL) {
                    int w = p->adjvex;
                    if (!visited[w]) {
                        visited[w] = 1;
                        queue[rear++] = w;
                    }
                    p = p->nextarc;
                }
            }
        }
    }
    return OK;
}

status Save(ALGraph G, char FileName[], ArcNode *p, FILE *fp, int i)
{
    if(p == NULL) return OK;
    Save(G, FileName, p->nextarc, fp, i);
    fprintf(fp, "%d %d\n", i, p->adjvex);
    return OK;
}
status SaveGraph(ALGraph G, char FileName[])
{
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
}
status LoadGraph(ALGraph &G, char FileName[])
{
    FILE *fp = fopen(FileName, "r");
    fscanf(fp, "%d%d%d", &G.vexnum, &G.arcnum, (int*)&G.kind);
    for(int i = 0; i < G.vexnum; i++) {
        fscanf(fp, "%d%s", &G.vertices[i].data.key, G.vertices[i].data.others);
        G.vertices[i].firstarc = NULL;
    }
    int u, v;
    while(fscanf(fp, "%d%d", &u, &v) == 2) {
        ArcNode *arc1 = (ArcNode*)malloc(sizeof(ArcNode));
        arc1->adjvex = v;
        arc1->nextarc = G.vertices[u].firstarc;
        G.vertices[u].firstarc = arc1;
    }
    fclose(fp);
    return OK;
}
void VerticesSetLessThanK(ALGraph G, KeyType v, int k) {
    int start = LocateVex(G, v);
    if (start == -1) {
        printf("起点不存在！\n");
        return;
    }
    int visited[MAX_VERTEX_NUM] = {0};
    int dist[MAX_VERTEX_NUM] = {0};
    int queue[MAX_VERTEX_NUM], front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = 1;
    dist[start] = 0;
    printf("距离小于%d的顶点集合：", k);
    while (front < rear) {
        int u = queue[front++];
        ArcNode *p = G.vertices[u].firstarc;
        while (p) {
            int w = p->adjvex;
            if (!visited[w]) {
                dist[w] = dist[u] + 1;
                if (dist[w] < k) {
                    printf("%d %s ", G.vertices[w].data.key, G.vertices[w].data.others);
                    queue[rear++] = w;
                }
                visited[w] = 1;
            }
            p = p->nextarc;
        }
    }
    printf("\n");
}

int ShortestPathLength(ALGraph G, KeyType v, KeyType w) {
    int start = LocateVex(G, v);
    int end = LocateVex(G, w);
    if (start == -1 || end == -1) return -1;
    int visited[MAX_VERTEX_NUM] = {0};
    int dist[MAX_VERTEX_NUM] = {0};
    int queue[MAX_VERTEX_NUM], front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = 1;
    dist[start] = 0;
    while (front < rear) {
        int u = queue[front++];
        if (u == end) return dist[u];
        ArcNode *p = G.vertices[u].firstarc;
        while (p) {
            int widx = p->adjvex;
            if (!visited[widx]) {
                visited[widx] = 1;
                dist[widx] = dist[u] + 1;
                queue[rear++] = widx;
            }
            p = p->nextarc;
        }
    }
    return -1;
}

int ConnectedComponentsNums(ALGraph G) {
    int visited[MAX_VERTEX_NUM] = {0};
    int count = 0;
    for (int i = 0; i < G.vexnum; ++i) {
        if (!visited[i]) {
            int queue[MAX_VERTEX_NUM], front = 0, rear = 0;
            queue[rear++] = i;
            visited[i] = 1;
            while (front < rear) {
                int u = queue[front++];
                ArcNode *p = G.vertices[u].firstarc;
                while (p) {
                    int w = p->adjvex;
                    if (!visited[w]) {
                        visited[w] = 1;
                        queue[rear++] = w;
                    }
                    p = p->nextarc;
                }
            }
            count++;
        }
    }
    return count;
}

int main() {
    GraphList graphList = {0};
    int current = -1;
    int op = 1;
    char gname[30];

    while (op) {
        system("cls");
        printf("\n\n");
        printf("      Menu for Graph Structure \n");
        printf("-------------------------------------------------\n");
        printf(" 1. CreateGraph     11. DFSTraverse\n");
        printf(" 2. DestroyGraph    12. BFSTraverse\n");
        printf(" 3. LocateVex       13. VerticesSetLessThanK\n");
        printf(" 4. PutVex          14. ShortestPathLength\n");
        printf(" 5. FirstAdjVex     15. ConnectedComponentsNums\n");
        printf(" 6. NextAdjVex      16. SaveGraph\n");
        printf(" 7. InsertVex       17. LoadGraph\n");
        printf(" 8. DeleteVex       18. AddGraph\n");
        printf(" 9. InsertArc       19. RemoveGraph\n");
        printf(" 10. DeleteArc      20. SwitchGraph\n");
        printf(" 0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("请选择你的操作[0~20]:");
        scanf("%d", &op);

        switch (op) {
        case 1: {
            if (graphList.length >= MAX_GRAPHS) {
                printf("图数量已达上限！\n"); getchar(); getchar(); break;
            }
            printf("请输入新图名称：");
            scanf("%s", gname);
            for (int i = 0; i < graphList.length; ++i) {
                if (strcmp(graphList.graphs[i].name, gname) == 0) {
                    printf("名称已存在！\n"); getchar(); getchar(); goto next;
                }
            }
            int n, m;
            printf("请输入顶点数：");
            scanf("%d", &n);
            VertexType* V = (VertexType*)malloc(sizeof(VertexType) * (n + 1));
            for (int i = 0; i < n; ++i) {
                printf("请输入第%d个顶点的key和others：", i + 1);
                scanf("%d %s", &V[i].key, V[i].others);
            }
            V[n].key = -1;
            printf("请输入边数：");
            scanf("%d", &m);
            KeyType (*VR)[2] = (KeyType(*)[2])malloc(sizeof(KeyType) * 2 * (m + 1));
            for (int i = 0; i < m; ++i) {
                printf("请输入第%d条边的两个顶点key：", i + 1);
                scanf("%d %d", &VR[i][0], &VR[i][1]);
            }
            VR[m][0] = VR[m][1] = -1;
            ALGraph G;
            if (CreateCraph(G, V, VR) == OK) {
                strcpy(graphList.graphs[graphList.length].name, gname);
                graphList.graphs[graphList.length].G = G;
                current = graphList.length;
                graphList.length++;
                printf("创建成功！\n");
            } else {
                printf("创建失败（有重复key或数据非法）！\n");
            }
            free(V);
            free(VR);
            getchar(); getchar();
            break;
        }
        case 2: {
            if (current == -1) { printf("请先切换到某个图！\n"); getchar(); getchar(); break; }
            DestroyGraph(graphList.graphs[current].G);
            printf("销毁成功！\n");
            getchar(); getchar();
            break;
        }
        case 3: {
            if (current == -1) { printf("请先切换到某个图！\n"); getchar(); getchar(); break; }
            printf("请输入要查找的key：");
            int k; scanf("%d", &k);
            int pos = LocateVex(graphList.graphs[current].G, k);
            if (pos != -1) printf("顶点位序为：%d\n", pos);
            else printf("未找到！\n");
            getchar(); getchar();
            break;
        }
        case 4: {
            if (current == -1) { printf("请先切换到某个图！\n"); getchar(); getchar(); break; }
            printf("请输入要赋值的key：");
            int k; scanf("%d", &k);
            VertexType v;
            printf("请输入新key和others：");
            scanf("%d %s", &v.key, v.others);
            if (PutVex(graphList.graphs[current].G, k, v) == OK)
                printf("赋值成功！\n");
            else
                printf("赋值失败（重复key或未找到）！\n");
            getchar(); getchar();
            break;
        }
        case 5: {
            if (current == -1) { printf("请先切换到某个图！\n"); getchar(); getchar(); break; }
            printf("请输入顶点key：");
            int k; scanf("%d", &k);
            int pos = FirstAdjVex(graphList.graphs[current].G, k);
            if (pos != -1)
                printf("第一邻接顶点位序为：%d\n", pos);
            else
                printf("无邻接顶点或未找到！\n");
            getchar(); getchar();
            break;
        }
        case 6: {
            if (current == -1) { printf("请先切换到某个图！\n"); getchar(); getchar(); break; }
            printf("请输入顶点key和邻接顶点key：");
            int v, w; scanf("%d %d", &v, &w);
            int pos = NextAdjVex(graphList.graphs[current].G, v, w);
            if (pos != -1)
                printf("下一个邻接顶点位序为：%d\n", pos);
            else
                printf("无下一个邻接顶点或未找到！\n");
            getchar(); getchar();
            break;
        }
        case 7: {
            if (current == -1) { printf("请先切换到某个图！\n"); getchar(); getchar(); break; }
            VertexType v;
            printf("请输入新顶点的key和others：");
            scanf("%d %s", &v.key, v.others);
            if (InsertVex(graphList.graphs[current].G, v) == OK)
                printf("插入成功！\n");
            else
                printf("插入失败（重复key或已满）！\n");
            getchar(); getchar();
            break;
        }
        case 8: {
            if (current == -1) { printf("请先切换到某个图！\n"); getchar(); getchar(); break; }
            printf("请输入要删除的顶点key：");
            int k; scanf("%d", &k);
            if (DeleteVex(graphList.graphs[current].G, k) == OK)
                printf("删除成功！\n");
            else
                printf("删除失败！\n");
            getchar(); getchar();
            break;
        }
        case 9: {
            if (current == -1) { printf("请先切换到某个图！\n"); getchar(); getchar(); break; }
            printf("请输入两个顶点的key：");
            int v, w; scanf("%d %d", &v, &w);
            if (InsertArc(graphList.graphs[current].G, v, w) == OK)
                printf("插入成功！\n");
            else
                printf("插入失败！\n");
            getchar(); getchar();
            break;
        }
        case 10: {
            if (current == -1) { printf("请先切换到某个图！\n"); getchar(); getchar(); break; }
            printf("请输入两个顶点的key：");
            int v, w; scanf("%d %d", &v, &w);
            if (DeleteArc(graphList.graphs[current].G, v, w) == OK)
                printf("删除成功！\n");
            else
                printf("删除失败！\n");
            getchar(); getchar();
            break;
        }
        case 11: {
            if (current == -1) { printf("请先切换到某个图！\n"); getchar(); getchar(); break; }
            printf("DFS遍历：");
            DFSTraverse(graphList.graphs[current].G, PrintVertex);
            printf("\n");
            getchar(); getchar();
            break;
        }
        case 12: {
            if (current == -1) { printf("请先切换到某个图！\n"); getchar(); getchar(); break; }
            printf("BFS遍历：");
            BFSTraverse(graphList.graphs[current].G, PrintVertex);
            printf("\n");
            getchar(); getchar();
            break;
        }
        case 13: {
            if (current == -1) { printf("请先切换到某个图！\n"); getchar(); getchar(); break; }
            printf("请输入起点key和距离k：");
            int v, k; scanf("%d %d", &v, &k);
            VerticesSetLessThanK(graphList.graphs[current].G, v, k);
            getchar(); getchar();
            break;
        }
        case 14: {
            if (current == -1) { printf("请先切换到某个图！\n"); getchar(); getchar(); break; }
            printf("请输入两个顶点key：");
            int v, w; scanf("%d %d", &v, &w);
            int len = ShortestPathLength(graphList.graphs[current].G, v, w);
            if (len == -1)
                printf("不可达或顶点不存在！\n");
            else
                printf("最短路径长度为：%d\n", len);
            getchar(); getchar();
            break;
        }
        case 15: {
            if (current == -1) { printf("请先切换到某个图！\n"); getchar(); getchar(); break; }
            int cnt = ConnectedComponentsNums(graphList.graphs[current].G);
            printf("连通分量个数为：%d\n", cnt);
            getchar(); getchar();
            break;
        }
        case 16: {
            if (current == -1) { printf("请先切换到某个图！\n"); getchar(); getchar(); break; }
            char fname[100];
            printf("请输入保存文件名：");
            scanf("%s", fname);
            SaveGraph(graphList.graphs[current].G, fname);
            printf("保存成功！\n");
            getchar(); getchar();
            break;
        }
        case 17: {
            if (graphList.length >= MAX_GRAPHS) {
                printf("图数量已达上限！\n"); getchar(); getchar(); break;
            }
            char fname[100], gname2[30];
            printf("请输入加载后图的名称：");
            scanf("%s", gname2);
            for (int i = 0; i < graphList.length; ++i) {
                if (strcmp(graphList.graphs[i].name, gname2) == 0) {
                    printf("名称已存在！\n"); getchar(); getchar(); goto next;
                }
            }
            printf("请输入文件名：");
            scanf("%s", fname);
            FILE *fp = fopen(fname, "r");
            if (!fp) {
                printf("文件不存在！\n");
                getchar(); getchar();
                break;
            }
            fclose(fp);
            ALGraph G;
            if (LoadGraph(G, fname) != OK) {
                printf("加载失败！\n");
                getchar(); getchar();
                break;
            }
            strcpy(graphList.graphs[graphList.length].name, gname2);
            graphList.graphs[graphList.length].G = G;
            current = graphList.length;
            graphList.length++;
            printf("加载成功！\n");
            getchar(); getchar();
            break;
        }
        case 18: {
            if (graphList.length >= MAX_GRAPHS) {
                printf("图数量已达上限！\n"); getchar(); getchar(); break;
            }
            printf("请输入新图名称：");
            scanf("%s", gname);
            for (int i = 0; i < graphList.length; ++i) {
                if (strcmp(graphList.graphs[i].name, gname) == 0) {
                    printf("名称已存在！\n"); getchar(); getchar(); goto next;
                }
            }
            graphList.graphs[graphList.length].G.vexnum = 0;
            graphList.graphs[graphList.length].G.arcnum = 0;
            strcpy(graphList.graphs[graphList.length].name, gname);
            current = graphList.length;
            graphList.length++;
            printf("添加成功！\n");
            getchar(); getchar();
            break;
        }
        case 19: {
            printf("请输入要移除的图名称：");
            scanf("%s", gname);
            int idx = -1;
            for (int i = 0; i < graphList.length; ++i) {
                if (strcmp(graphList.graphs[i].name, gname) == 0) { idx = i; break; }
            }
            if (idx == -1) { printf("未找到！\n"); getchar(); getchar(); break; }
            DestroyGraph(graphList.graphs[idx].G);
            for (int j = idx; j < graphList.length - 1; ++j)
                graphList.graphs[j] = graphList.graphs[j + 1];
            graphList.length--;
            if (current == idx) current = -1;
            printf("移除成功！\n");
            getchar(); getchar();
            break;
        }
        case 20: {
            printf("请输入要切换的图名称：");
            scanf("%s", gname);
            int idx = -1;
            for (int i = 0; i < graphList.length; ++i) {
                if (strcmp(graphList.graphs[i].name, gname) == 0) { idx = i; break; }
            }
            if (idx == -1) { printf("未找到！\n"); getchar(); getchar(); break; }
            current = idx;
            printf("已切换到：%s\n", graphList.graphs[current].name);
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