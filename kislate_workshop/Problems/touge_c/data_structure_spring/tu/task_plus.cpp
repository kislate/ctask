#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <set>
#include <unordered_map>
#include <windows.h>
using namespace std;

// ====== 类型定义区 ======
#define MAX_VERTEX_NUM 100
#define OK 1
#define ERROR 0
typedef int status;
typedef int KeyType;

typedef struct {
    KeyType key;
    char others[20];
} VertexType;

typedef struct ArcNode {
    int adjvex;
    struct ArcNode *nextarc;
} ArcNode;

typedef struct {
    VertexType data;
    ArcNode *firstarc;
} VexNode;

typedef enum { UDG = 0, DG, UDN, DN } GraphKind;

typedef struct {
    VexNode vertices[MAX_VERTEX_NUM];
    int vexnum, arcnum;
    GraphKind kind;
} ALGraph;

// ====== 多图管理结构 ======
typedef struct {
    struct {
        char name[30];
        ALGraph G;
    } elem[10];
    int length;
} ALGrapHS;

// ====== 函数声明区（demo.md中函数） ======
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
void visit(VertexType v);
status DFSTraverse(ALGraph &G, void (*visit)(VertexType));
status BFSTraverse(ALGraph &G, void (*visit)(VertexType));
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);
void PrintAdjMatrix(ALGraph &G);
void PrintAllVertexAndIndex(ALGraph &G);

// ====== 附加功能函数声明 ======
void VerticesSetLessThanK(ALGraph &G, KeyType v, int k);
int ShortestPathLength(ALGraph &G, KeyType v, KeyType w);
int ConnectedComponentsNums(ALGraph &G);

// ====== 多图管理函数 ======
int AddGraph(ALGrapHS &Graphs, char name[]) {
    for(int i = 0; i < Graphs.length; i++)
        if(strcmp(Graphs.elem[i].name, name) == 0)
            return ERROR;
    if(Graphs.length >= 10) return ERROR;
    strcpy(Graphs.elem[Graphs.length].name, name);
    Graphs.elem[Graphs.length].G.vexnum = 0;
    Graphs.elem[Graphs.length].G.arcnum = 0;
    Graphs.elem[Graphs.length].G.kind = UDG;
    Graphs.length++;
    return OK;
}
int RemoveGraph(ALGrapHS &Graphs, char name[]) {
    int i;
    for(i = 0; i < Graphs.length; i++)
        if(strcmp(Graphs.elem[i].name, name) == 0) break;
    if(i == Graphs.length) return ERROR;
    DestroyGraph(Graphs.elem[i].G);
    for(int j = i; j < Graphs.length - 1; j++)
        Graphs.elem[j] = Graphs.elem[j + 1];
    Graphs.length--;
    return OK;
}
int LocateGraph(ALGrapHS Graphs, char name[]) {
    for(int i = 0; i < Graphs.length; i++)
        if(strcmp(Graphs.elem[i].name, name) == 0)
            return i + 1;
    return ERROR;
}
void printAllGraphNames(ALGrapHS &Graphs) {
    printf("      当前已有图数量：%d\n", Graphs.length);
    for(int i = 0; i < Graphs.length; i++)
        printf("      %d. %s\n", i + 1, Graphs.elem[i].name);
}

// ====== 附加功能实现 ======
void VerticesSetLessThanK(ALGraph &G, KeyType v, int k) {
    int start = LocateVex(G, v);
    if(start == -1) {
        printf("      未找到该顶点！\n");
        return;
    }
    int dist[MAX_VERTEX_NUM] = {0};
    int visited[MAX_VERTEX_NUM] = {0};
    queue<int> q;
    q.push(start);
    visited[start] = 1;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        ArcNode *p = G.vertices[u].firstarc;
        while(p) {
            if(!visited[p->adjvex]) {
                dist[p->adjvex] = dist[u] + 1;
                if(dist[p->adjvex] < k) {
                    printf("      %d %s\n", G.vertices[p->adjvex].data.key, G.vertices[p->adjvex].data.others);
                    q.push(p->adjvex);
                }
                visited[p->adjvex] = 1;
            }
            p = p->nextarc;
        }
    }
}
int ShortestPathLength(ALGraph &G, KeyType v, KeyType w) {
    int start = LocateVex(G, v);
    int end = LocateVex(G, w);
    if(start == -1 || end == -1) return -1;
    int dist[MAX_VERTEX_NUM];
    for(int i = 0; i < MAX_VERTEX_NUM; i++) dist[i] = -1;
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        if(u == end) return dist[u];
        ArcNode *p = G.vertices[u].firstarc;
        while(p) {
            if(dist[p->adjvex] == -1) {
                dist[p->adjvex] = dist[u] + 1;
                q.push(p->adjvex);
            }
            p = p->nextarc;
        }
    }
    return -1;
}
int ConnectedComponentsNums(ALGraph &G) {
    int visited[MAX_VERTEX_NUM] = {0};
    int cnt = 0;
    for(int i = 0; i < G.vexnum; i++) {
        if(!visited[i]) {
            cnt++;
            queue<int> q;
            q.push(i);
            visited[i] = 1;
            while(!q.empty()) {
                int u = q.front(); q.pop();
                ArcNode *p = G.vertices[u].firstarc;
                while(p) {
                    if(!visited[p->adjvex]) {
                        visited[p->adjvex] = 1;
                        q.push(p->adjvex);
                    }
                    p = p->nextarc;
                }
            }
        }
    }
    return cnt;
}

// ====== demo.md函数实现区 ======
#include <queue>
#include <set>
#include <unordered_map>
using namespace std;

status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2]) {
    if(V[0].key == -1 && VR[0][0] == -1) {
        return ERROR;
    }
    unordered_map<int, int> hash_map;
    set<pair<int, int>> edge_set;
    VertexType node = V[0];
    G.vexnum = 0;
    while(node.key != -1){
        G.vertices[G.vexnum].data = node;
        G.vertices[G.vexnum].firstarc = NULL;
        if(hash_map.find(node.key) != hash_map.end()){
            return ERROR;
        }
        hash_map[node.key] = G.vexnum;
        G.vexnum++;
        node = V[G.vexnum];
    }
    G.arcnum = 0;
    while(VR[G.arcnum][0] != -1){
        int u = VR[G.arcnum][0];
        int v = VR[G.arcnum][1];
        int x = min(u, v), y = max(u, v);
        if(edge_set.count({x, y}) || x == y) {
        } else {
            edge_set.insert({x, y});
            if(hash_map.find(u) == hash_map.end() || hash_map.find(v) == hash_map.end()){
                return ERROR;
            }
            ArcNode *arc = (ArcNode *)malloc(sizeof(ArcNode));
            arc->adjvex = hash_map[v];
            arc->nextarc = G.vertices[hash_map[u]].firstarc;
            G.vertices[hash_map[u]].firstarc = arc;
            G.kind = UDG;
            if(G.kind == UDG || G.kind == UDN){
                ArcNode *arc2 = (ArcNode *)malloc(sizeof(ArcNode));
                arc2->adjvex = hash_map[u];
                arc2->nextarc = G.vertices[hash_map[v]].firstarc;
                G.vertices[hash_map[v]].firstarc = arc2;
            }
            G.arcnum++;
        }
    }
    return OK;
}

status DestroyGraph(ALGraph &G) {
    if(G.vexnum == 0){
        return ERROR;
    }
    for(int i = 0; i < G.vexnum; i++){
        ArcNode *p = G.vertices[i].firstarc;
        while(p){
            ArcNode *q = p;
            p = p->nextarc;
            free(q);
        }
        G.vertices[i].firstarc = NULL;
    }
    G.vexnum = 0;
    G.arcnum = 0;
    return OK;
}

int LocateVex(ALGraph G, KeyType u) {
    for(int i = 0; i < G.vexnum; i++){
        if(G.vertices[i].data.key == u){
            return i;
        }
    }
    return -1;
}

status PutVex(ALGraph &G, KeyType u, VertexType value) {
    int pos = LocateVex(G, u);
    if(pos == -1 || (LocateVex(G, value.key) != -1 && LocateVex(G, value.key) != pos)){
        return ERROR;
    }
    G.vertices[pos].data = value;
    return OK;
}

int FirstAdjVex(ALGraph G, KeyType u) {
    int pos = LocateVex(G, u);
    if(pos == -1){
        return -1;
    }
    ArcNode *p = G.vertices[pos].firstarc;
    if(p == NULL){
        return -1;
    }
    return p->adjvex;
}

int NextAdjVex(ALGraph G, KeyType v, KeyType w) {
    int pos = LocateVex(G, v);
    int next = LocateVex(G, w);
    if(pos == -1){
        return -1;
    }
    ArcNode *p = G.vertices[pos].firstarc;
    while(p){
        if(p->adjvex == next){
            p = p->nextarc;
            if(p){
                return p->adjvex;
            } else {
                return -1;
            }
        }
        p = p->nextarc;
    }
    return -1;
}

status InsertVex(ALGraph &G, VertexType v) {
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
}

status DeleteVex(ALGraph &G, KeyType v) {
    if(G.vexnum == 0) return ERROR;
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

status InsertArc(ALGraph &G, KeyType v, KeyType w) {
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
}

status DeleteArc(ALGraph &G, KeyType v, KeyType w) {
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
}

void visit(VertexType v) {
    printf("%d %s\n", v.key, v.others);
}

int visited[MAX_VERTEX_NUM] = {0};
void DFS(ALGraph &G, int v, void (*visit)(VertexType)) {
    visited[v] = 1;
    visit(G.vertices[v].data);
    ArcNode *p = G.vertices[v].firstarc;
    while(p) {
        if(!visited[p->adjvex]) {
            DFS(G, p->adjvex, visit);
        }
        p = p->nextarc;
    }
}

status DFSTraverse(ALGraph &G, void (*visit)(VertexType)) {
    if(G.vexnum == 0) return ERROR;
    for(int i = 0; i < MAX_VERTEX_NUM; i++) visited[i] = 0;
    for(int i = 0; i < G.vexnum; i++) {
        if(!visited[i]) {
            DFS(G, i, visit);
        }
    }
    return OK;
}

status BFSTraverse(ALGraph &G, void (*visit)(VertexType)) {
    for(int i = 0; i < G.vexnum; i++) visited[i] = 0;
    queue<int> heap;
    for(int i = 0; i < G.vexnum; i++){
        heap.push(i);
        while(!heap.empty()){
            int v = heap.front();
            heap.pop();
            if(visited[v]) continue;
            visited[v] = 1;
            visit(G.vertices[v].data);
            ArcNode *p = G.vertices[v].firstarc;
            while(p){
                if(!visited[p->adjvex]){
                    heap.push(p->adjvex);
                }
                p = p->nextarc;
            }
        }
    }
    return OK;
}

// 文件保存/加载
status Save(ALGraph G, char FileName[], ArcNode *p, FILE *fp, int i) {
    if(p == NULL) return OK;
    Save(G, FileName, p->nextarc, fp, i);
    fprintf(fp, "%d %d\n", i, p->adjvex);
}
status SaveGraph(ALGraph G, char FileName[]) {
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
}
status LoadGraph(ALGraph &G, char FileName[]) {
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
}

// ====== 单图菜单与主控 ======
void singleGraphMenu() {
    printf("\n");
    printf("      ========== 单图操作菜单 ==========\n");
    printf("      1. 创建邻接图          8. 删除顶点\n");
    printf("      2. 销毁图              9. 插入边/弧\n");
    printf("      3. 查找顶点           10. 删除边/弧\n");
    printf("      4. 顶点赋值           11. 深度优先遍历\n");
    printf("      5. 第一邻接点         12. 广度优先遍历\n");
    printf("      6. 下一个邻接点       13. 保存图到文件\n");
    printf("      7. 插入顶点           14. 从文件加载图\n");
    printf("      15. 距离小于k的顶点集合\n");
    printf("      16. 顶点间最短路径长度\n");
    printf("      17. 连通分量个数\n");
    printf("      18. 打印邻接矩阵\n");
    printf("      19. 打印所有顶点及位序\n");
    printf("      0. 返回多图菜单\n");
    printf("      =====================================\n");
    printf("      请选择你的操作[0~19]:");
}

void singleGraphControl(ALGraph &G) {
    int op = 1;
    VertexType v, value;
    KeyType u, w;
    KeyType VR[MAX_VERTEX_NUM][2];
    VertexType V[MAX_VERTEX_NUM];
    while(op) {
        system("cls");
        singleGraphMenu();
        scanf("%d", &op);

        if(op != 1 && op != 2 && op != 14 && G.vexnum == 0) {
            printf("      图不存在！\n");
            getchar(); printf("      按任意键继续...\n"); getchar();
            continue;
        }

        switch(op) {
            case 1: {
                if(G.vexnum != 0) {
                    printf("      当前图已存在，是否销毁并覆盖？(y/n)：");
                    char ch;
                    getchar();
                    ch = getchar();
                    if(ch != 'y' && ch != 'Y') {
                        printf("      已取消创建操作。\n");
                        printf("      按任意键继续...\n"); getchar();
                        break;
                    }
                    DestroyGraph(G);
                }
                printf("      请输入顶点序列（格式：关键字 信息），以-1结束：\n");
                int i = 0;
                do {
                    scanf("%d%s", &V[i].key, V[i].others);
                } while(V[i++].key != -1);
                printf("      请输入边序列（格式：关键字1 关键字2），以-1 -1结束：\n");
                i = 0;
                do {
                    scanf("%d%d", &VR[i][0], &VR[i][1]);
                } while(VR[i++][0] != -1);
                if(CreateCraph(G, V, VR) == OK)
                    printf("      图创建成功！\n");
                else
                    printf("      图创建失败，存在重复关键字或非法边！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 2: {
                if(G.vexnum == 0) printf("      图不存在，无法销毁！\n");
                else if(DestroyGraph(G) == OK) printf("      图销毁成功！\n");
                else printf("      图销毁失败！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 3: {
                printf("      请输入要查找的顶点关键字：");
                scanf("%d", &u);
                int pos = LocateVex(G, u);
                if(pos != -1)
                    printf("      找到关键字为%d的顶点，位序为：%d\n", u, pos);
                else
                    printf("      未找到关键字为%d的顶点！\n", u);
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 4: {
                printf("      请输入要赋值的顶点关键字：");
                scanf("%d", &u);
                printf("      请输入新关键字和信息：");
                scanf("%d%s", &value.key, value.others);
                if(PutVex(G, u, value) == OK)
                    printf("      顶点赋值成功！\n");
                else
                    printf("      顶点赋值失败，可能关键字不存在或新关键字已存在！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 5: {
                printf("      请输入顶点关键字：");
                scanf("%d", &u);
                int pos = FirstAdjVex(G, u);
                if(pos != -1)
                    printf("      第一邻接顶点位序为：%d，关键字为：%d\n", pos, G.vertices[pos].data.key);
                else
                    printf("      未找到邻接顶点！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 6: {
                printf("      请输入顶点关键字v和邻接顶点关键字w：");
                scanf("%d%d", &u, &w);
                int pos = NextAdjVex(G, u, w);
                if(pos != -1)
                    printf("      下一个邻接顶点位序为：%d，关键字为：%d\n", pos, G.vertices[pos].data.key);
                else
                    printf("      未找到下一个邻接顶点！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 7: {
                printf("      请输入要插入的顶点（关键字 信息）：");
                scanf("%d%s", &v.key, v.others);
                if(InsertVex(G, v) == OK)
                    printf("      顶点插入成功！\n");
                else
                    printf("      顶点插入失败！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 8: {
                printf("      请输入要删除的顶点关键字：");
                scanf("%d", &u);
                if(DeleteVex(G, u) == OK)
                    printf("      顶点删除成功！\n");
                else
                    printf("      顶点删除失败！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 9: {
                printf("      请输入插入弧的两个顶点关键字v w：");
                scanf("%d%d", &u, &w);
                if(InsertArc(G, u, w) == OK)
                    printf("      弧插入成功！\n");
                else
                    printf("      弧插入失败！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 10: {
                printf("      请输入要删除的弧的两个顶点关键字v w：");
                scanf("%d%d", &u, &w);
                if(DeleteArc(G, u, w) == OK)
                    printf("      弧删除成功！\n");
                else
                    printf("      弧删除失败！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 11: {
                printf("      深度优先遍历结果：\n");
                DFSTraverse(G, visit);
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 12: {
                printf("      广度优先遍历结果：\n");
                BFSTraverse(G, visit);
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 13: {
                printf("      请输入文件名：");
                char filename[100];
                scanf("%s", filename);
                SaveGraph(G, filename);
                printf("      图已保存到文件：%s\n", filename);
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 14: {
                printf("      请输入文件名：");
                char filename[100];
                scanf("%s", filename);
                LoadGraph(G, filename);
                printf("      图已从文件加载：%s\n", filename);
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 15: {
                printf("      请输入顶点关键字和距离k：");
                int k;
                scanf("%d%d", &u, &k);
                printf("      距离小于%d的顶点集合：\n", k);
                VerticesSetLessThanK(G, u, k);
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 16: {
                printf("      请输入两个顶点关键字：");
                scanf("%d%d", &u, &w);
                int len = ShortestPathLength(G, u, w);
                if(len != -1)
                    printf("      最短路径长度为：%d\n", len);
                else
                    printf("      不连通或顶点不存在！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 17: {
                int cnt = ConnectedComponentsNums(G);
                printf("      图的连通分量个数为：%d\n", cnt);
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            }
            case 18: {
                PrintAdjMatrix(G);
                printf("      按任意键继续...\n"); getchar(); getchar();
                break;
            }
            case 19: {
                PrintAllVertexAndIndex(G);
                printf("      按任意键继续...\n"); getchar(); getchar();
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

// ====== 邻接矩阵美观输出 ======
void PrintAdjMatrix(ALGraph &G) {
    if(G.vexnum == 0) {
        printf("      图为空！\n");
        return;
    }
    int matrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM] = {0};
    for(int i = 0; i < G.vexnum; i++) {
        ArcNode *p = G.vertices[i].firstarc;
        while(p) {
            matrix[i][p->adjvex] = 1;
            p = p->nextarc;
        }
    }
    // 输出表头
    printf("\n      邻接矩阵：\n\n");
    printf("        ");
    for(int i = 0; i < G.vexnum; i++)
        printf("%6d", G.vertices[i].data.key);
    printf("\n");
    printf("         ");
    for(int i = 0; i < G.vexnum; i++)
        printf("------");
    printf("\n");
    for(int i = 0; i < G.vexnum; i++) {
        printf("%6d |", G.vertices[i].data.key);
        for(int j = 0; j < G.vexnum; j++) {
            printf("%6d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void PrintAllVertexAndIndex(ALGraph &G) {
    if(G.vexnum == 0) {
        printf("      图为空！\n");
        return;
    }
    printf("      顶点位序列表：\n");
    printf("      位序    关键字    信息\n");
    printf("      --------------------------\n");
    for(int i = 0; i < G.vexnum; i++) {
        printf("      %4d    %6d    %-10s\n", i, G.vertices[i].data.key, G.vertices[i].data.others);
    }
}

// ====== 多图菜单与主控 ======
void multiGraphMenu() {
    printf("\n");
    printf("      ========== 多图管理菜单 ==========\n");
    printf("      1. 新建图\n");
    printf("      2. 删除图\n");
    printf("      3. 打印所有图名\n");
    printf("      4. 进入某个图操作\n");
    printf("      0. 退出系统\n");
    printf("      =====================================\n");
    printf("      请选择你的操作[0~4]:");
}

int main(void) {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    ALGrapHS Graphs = {0};
    int op = 1;
    char name[30];
    int pos;
    while(op) {
        system("cls");
        multiGraphMenu();
        scanf("%d", &op);
        switch(op) {
            case 1:
                printf("      请输入新图的名称：");
                scanf("%s", name);
                if(AddGraph(Graphs, name) == OK) printf("      新建图成功！\n");
                else printf("      新建图失败！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            case 2:
                printf("      请输入要删除的图名称：");
                scanf("%s", name);
                if(RemoveGraph(Graphs, name) == OK) printf("      删除图成功！\n");
                else printf("      删除图失败，可能不存在该图！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            case 3:
                printAllGraphNames(Graphs);
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
            case 4:
                printf("      请输入要操作的图名称：");
                scanf("%s", name);
                pos = LocateGraph(Graphs, name);
                if(pos > 0) {
                    printf("      进入图 [%s] 的操作\n", name);
                    singleGraphControl(Graphs.elem[pos-1].G);
                } else {
                    printf("      图 [%s] 不存在！\n", name);
                    getchar(); printf("      按任意键继续...\n"); getchar();
                }
                break;
            case 0:
                for(int i = 0; i < Graphs.length; i++) DestroyGraph(Graphs.elem[i].G);
                printf("      感谢使用图管理系统，再见！\n");
                break;
            default:
                printf("      输入有误，请重新输入！\n");
                getchar(); printf("      按任意键继续...\n"); getchar();
                break;
        }
    }
    return 0;
}
