#include <stdio.h>
#include <stdlib.h>
#define BLOCK_SIZE 10

typedef struct {
    int *array;
    int size;
} Array;

//数组的创建
Array array_create(int size);
//数组的释放
void array_free(Array *a);
//数组的指定位
int* array_at(Array *a,int index);
//数组的大小
int array_size(const Array *a);
//数组的涨大
void array_inflate(Array *a,int more_size);
//数组的遍历
void array_foreach(Array *a,int size);

int main(int argc, const char * argv[])
{
    Array a = array_create(3);

    printf("a.init_size = %d\n",array_size(&a));
    
//    printf("a.arry[0] = %d\n",a.array[0]);
//    printf("a.arry[1] = %d\n",a.array[1]);
//    printf("a.arry[2] = %d\n",a.array[2]);
//    printf("a.arry[5] = %d\n",a.array[5]);
//    printf("a.arry[10] = %d\n",a.array[10]);
//    printf("a.arry[11] = %d\n",a.array[11]);
    
    
    
    *array_at(&a, 0) = 10;
    *array_at(&a, 1) = 20;
    *array_at(&a, 2) = 30;
//    *array_at(&a,5) = 50;
//    *array_at(&a,11) = 110;

    printf("a.arry[0] = %d\n",a.array[0]);
    printf("a.arry[1] = %d\n",a.array[1]);
    printf("a.arry[2] = %d\n",a.array[2]);
//    p
    
//    printf("a.size = %d\n",a.size);

    int number=0;
    int cnt = 0;
    while (number != -1) {
        printf("请输入第%d个整数值，输入-1结束:\n",cnt+1);
        scanf("%d",&number);
        if (number != -1) {
            *array_at(&a, cnt) = number;
            cnt++;
        }
//        scanf("%d",array_at(&a, cnt++)); //也可以
    }
   
    /*
//    //遍历
//    for (int i =0; i<cnt; i++) {
//        printf("a.array[%i] = %d\n",i,a.array[i]);
//    }
//    printf("a.current_size = %d\n",a.size);
    */
    array_foreach(&a,cnt);
//    array_foreach(&a,a.size); //本可以不需要a.size的，主要是解决没有赋值的元素位置乱码的问题
//    array_foreach(&a,cnt);//本可以不需要a.size的，用cnt作为参数 ,主要是解决没有赋值的元素位置乱码的问题
    printf("%d\n",a.size);
    array_free(&a);
    
    return 0;
}

Array array_create(int init_size){
    Array a;
    a.size = init_size;
    a.array = (int *)malloc(sizeof(int)*(a.size));
    return a;
    
}
//数组的释放
void array_free(Array *a){
    free(a->array);
    a->array = NULL;
    a->size = 0;
}
//求数组的大小size
int array_size(const Array *a){
    return a->size;
}

//指定位置拿数组的值
int* array_at(Array *a,int index){
    //如果index大于a的size，需要将数组涨大
    if (index >= a->size) {
        array_inflate(a, (index/BLOCK_SIZE+1)*BLOCK_SIZE - a->size);
    }
    return &(a->array[index]);

}
//数组的增长
void array_inflate(Array *a,int more_size){
    
    int *p = (int*)malloc((a->size + more_size)*sizeof(int));
    for (int i = 0; i<a->size; i++) {
        p[i] = a->array[i];
    }
    free(a->array);
    a->array = p;
    a->size = a->size+more_size;
}

//void array_foreach(Array *a,int size){
//
//    for (int i =0; i<a->size; i++) {
//        printf("a.array[%i] = %d\n",i,a->array[i]);
//    }
//}


void array_foreach(Array *a,int size){
    
    for (int i =0; i<a->size; i++) {
        printf("a.array[%i] = %d\n",i,a->array[i]);
    }
}