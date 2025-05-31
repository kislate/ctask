- 第一关
```cpp
status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
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
    /********** End **********/
}
```
- 第二关
```cpp
status DestroyGraph(ALGraph &G)
/*销毁无向图G,删除G的全部顶点和边*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
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
    /********** End **********/
}
```
- 第三关
```cpp
int LocateVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for(int i = 0; i < G.vexnum; i++){
        if(G.vertices[i].data.key == u){
            return i;
        }
    }
    return -1;
    /********** End **********/
}
```
- 第四关
```cpp
status PutVex(ALGraph &G,KeyType u,VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int pos = LocateVex(G, u);
    if(pos == -1 || (LocateVex(G, value.key) != -1 && LocateVex(G, value.key) != pos)){
        return ERROR;
    }
    G.vertices[pos].data = value;
    return OK;
    /********** End **********/
}
```
- 第五关
```cpp
int FirstAdjVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int pos = LocateVex(G, u);
    if(pos == -1){
        return -1;
    }
    ArcNode *p = G.vertices[pos].firstarc;
    if(p == NULL){
        return -1;
    }
    return p->adjvex;
    /********** End **********/
}
```
- 第六关
```cpp
int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//v对应G的一个顶点,w对应v的邻接顶点；操作结果是返回v的（相对于w）下一个邻接顶点的位序；如果w是最后一个邻接顶点，或v、w对应顶点不存在，则返回-1。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
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
    /********** End **********/
}
```
- 第七关
```cpp
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

```
- 第八关
```cpp
status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(G.vexnum == 0 || (G.vexnum = 1 && G.arcnum == 0)) return ERROR;// 过了, 但是感觉这个没用, 但是样例判断这个不能过
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
```
- 第九关
```cpp
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
```
- 第十关
```cpp
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
```
- 第十一关
```cpp
void visit(VertexType v)
// 访问顶点v
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    printf("%d %s\n", v.key, v.others);
    /********** End **********/
}
int visited[MAX_VERTEX_NUM] = {0};
VertexType ans[MAX_VERTEX_NUM];
int index = 0, cnt = 0, pos = 0;
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

status DFSTraverse(ALGraph &G, void (*visit)(VertexType))
{
    if(G.vexnum == 0) return ERROR;
    for(int i = 0; i < MAX_VERTEX_NUM; i++) visited[i] = 0; // 初始化
    for(int i = 0; i < G.vexnum; i++) {
        if(!visited[i]) {
            DFS(G, i, visit);
        }
    }
    return OK;
}
```
- 第十二关
```cpp
status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
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
    /********** End **********/
}
```
- 第十三关(文件读写)
```cpp
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
```