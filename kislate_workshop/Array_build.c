
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
    return &(a->array[index]);//返回这个增长后的数组
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
    while(number != -1){
        printf("请输入第%d个元素的值：",cnt);
        scanf("%d",&number);
        if(number != -1){
            *array_at(&a,cnt) = number;
            cnt++;
        }
    }//这串代码就是不断给这个结构体赋值；

    printf("数组的大小是：%d\n",arrat_size(&a));
    printf("数组的元素是：");
    array_foreach(&a,cnt);//size和cnt不一定是一样的
    printf("\n");//这个是遍历数组的代码

    
    return 0;

}

//在普通的数组实现的过程中
//当你使用malloc分配空间的时候，虽然只赋值了3个元素
//但是如果你直接给第10号赋值，它也会正常地打印这个第十号数值，因为你是在动态区分配的
//但是实际上这是一个很隐蔽的越界问题，因为你只分配了3个元素，但是你却给第10号赋值了

//不完美的地方*2

//不能完全利用数组的空间
//而且数据迁移的时候，如果数组足够大，那么就会存在一段时间，同时占用了两倍数组所需的内存，导致速率变慢

//解决方案

//链表

