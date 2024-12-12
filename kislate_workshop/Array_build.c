
#include<stdio.h>
#include<stdlib.h>
#define BLOCK_SIZE 10

typedef struct {
    int size;
    int *array;
}Array;//这个数组是定义在一个结构体中的，里面包含了数组大小和数组的指针

Array arr_create(int size){
    Array a;
    a.size = size;
    a.array = (int*)malloc(sizeof(int)*size);
    return a;
}

//求数组的大小size
int arrat_size(const Array *a){
    return a->size;
}

//数组的增长
void array_inflate(Array *a,int more_size){
    int *p = (int*)malloc((a->size+more_size)*sizeof(int));
    int i;
    for(i=0;i<a->size;i++){
        p[i] = a->array[i];
    }
    free(a->array);
    a->array = p;
    a->size +=more_size;
}

//指定数组的大小size
int *array_at(Array *a,int index){
    //如果数组的大小不够，就扩充数组
    if(index>=a->size){
        array_inflate(a,(index/BLOCK_SIZE+1)*BLOCK_SIZE-a->size);
    }
    return &(a->array[index]);
};

//数组的释放
void array_free(Array *a){
    free(a->array);
    a->array = NULL;
    a->size = 0;
}

//数组的遍历
void array_foreach(Array *a,int size){
    for(int i;i<a->size;i++){
        printf("%d",a->array[i]);
    }
}


int main(int argc,char *argv[])
{
    Array a=arr_create(3);//只有3个元素的数组

    printf("a.lint_size = %d\n",arrat_size(&a));

    *array_at(&a,0) = 10;
    *array_at(&a,1) = 20;
    *array_at(&a,2) = 30;
    *array_at(&a,3) = 40;//这个时候数组的大小不够，会自动扩充数组的大小

    printf("a[0] = %d\n",*array_at(&a,0));
    printf("a[1] = %d\n",*array_at(&a,1));
    printf("a[2] = %d\n",*array_at(&a,2));

    int number = 0;
    int cnt=0;
    
    return 0;
}

