struct intNode *createList(){
    struct intNode *head,*p;
    int x;
    head=NULL;
    scanf("%d",&x);
    if(x){
        p=(struct intNode *)malloc(sizeof(struct intNode));
        p->data=x;
        head=p;
        p->next=createList();
    }
    return head;
}