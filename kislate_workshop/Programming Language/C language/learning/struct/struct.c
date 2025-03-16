#include<stdio.h>
int main(void)
{
    //结构体的存储空间不是所有空间的总和，而是求存储最大的那个元素类型的倍数来算，]
    //特例如果存储空间不够，就会重新开辟的存储空间（最大的那一个），并且将需要存储的数据
    //如果剩余的空间够就不会开辟了
    struct Person{
        char c;
        
        int age;

        double height;
    };
    struct Person sp1;

    printf("size = %zu\n",sizeof(sp1));//16

    struct Person2{
        char c;
        
        double height;

        int age;
    };

    struct Person2 kislate;
    printf("size2 = %zu\n",sizeof(kislate)); //24
    //因为一开始开辟了八个，但是放c的时候占了1，导致height又开辟了一个，之后int又开辟了一个

    
    struct{
        char a;

        int b;
    } kis;//这个也可以但是以后会很难用。

    typedef struct 
    {
        int a;

        char c;
    } struct_Name;//这样以后声明一个struct_Name的时候可以省略前面的struct

    struct_Name sp;

    struct_Name *sip=&sp;

    sp.a=1;

    sp.c=2;

    (*sip).a=3;

    sip->a =4;//就这样

    //结构体其实就可以看成一个变量类型，所以声明数组也是可以的
    typedef struct{
        char names[5];
        int toll;
        int wage;
    } bumens;

    bumens str_Arr[5];//={}*5;

    //结构体是可以套结构体的，这个你在c++见多了
    /*
    struct name{
    struct name2{
    
    
    };
    
    
    };
    */
   //这个就是用一堆点来访问数据；
}