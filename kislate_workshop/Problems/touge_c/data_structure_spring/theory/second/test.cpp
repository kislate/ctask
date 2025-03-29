void adjust(DuLinkList L) {
    if (L == NULL || L->next == L || L->next->next == L) {
        return;  // 链表为空或只有一个元素时，不需要调整
    }

    DuLinkList oddlist, evenlist, oddtail, eventail;
    oddlist = (DuLinkList)malloc(sizeof(struct Dnode));
    evenlist = (DuLinkList)malloc(sizeof(struct Dnode));
    oddtail = oddlist;
    eventail = evenlist;

    oddlist->next = oddlist;
    evenlist->next = evenlist;
    oddlist->prior = oddlist;
    evenlist->prior = evenlist;

    DuLinkList p = L->next;  // 从头结点的下一个节点开始
    int cnt = 1;

    // 遍历链表，将奇数位置节点和偶数位置节点分别存入两个链表
    while (p != L) {
        if (cnt % 2 == 1) {  // 奇数位置节点
            oddtail->next = p;
            p->prior = oddtail;
            oddtail = p;
        } else {  // 偶数位置节点
            eventail->next = p;
            p->prior = eventail;
            eventail = p;
        }
        cnt++;
        p = p->next;
    }

    // 合并两个链表：奇数部分 + 偶数部分
    oddtail->next = evenlist->next;
    if (evenlist->next != L) {
        evenlist->next->prior = oddtail;
    }
    L->next = oddlist->next;
    oddlist->next->prior = L;

    eventail->next = L;
    L->prior = eventail;

    // 释放临时头节点
    free(oddlist);
    free(evenlist);
}
