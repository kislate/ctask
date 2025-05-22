void saveNode(BiTree T, FILE* fp) {
    if (T == NULL) {
        fputc(0, fp);
        return;
    }
    fputc(1, fp);
    fwrite(&T->data, sizeof(TElemType), 1, fp);
    saveNode(T->lchild, fp);
    saveNode(T->rchild, fp);
}

status SaveBiTree(BiTree T, const char FileName[]) {
    FILE* fp;
    if ((fp = fopen(FileName, "wb")) == NULL) return ERROR;
    saveNode(T, fp);
    fclose(fp);
    return OK;
}

// 辅助函数：递归加载节点
void loadNode(BiTree& T, FILE* fp) {
    int flag = fgetc(fp);
    if (flag == 0) {
        T = NULL;
        return;
    }
    T = (BiTNode*)malloc(sizeof(BiTNode));
    fread(&T->data, sizeof(TElemType), 1, fp);
    loadNode(T->lchild, fp);
    loadNode(T->rchild, fp);
}

status LoadBiTree(BiTree& T, const char FileName[]) {
    FILE* fp;
    if ((fp = fopen(FileName, "rb")) == NULL) return ERROR;
    loadNode(T, fp);
    fclose(fp);
    return OK;
}