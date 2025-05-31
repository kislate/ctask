#include <string.h>

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

status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!check(V, VR))
        return ERROR;
    int k = 0;
    G.arcnum = G.vexnum = 0;
    while (V[k].key != -1) {
        G.vexnum++; // 结点个数为key不为-1的个数
        G.vertices[k].data.key = V[k].key; // 从0号结点开始使用
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
    /********** End **********/
}