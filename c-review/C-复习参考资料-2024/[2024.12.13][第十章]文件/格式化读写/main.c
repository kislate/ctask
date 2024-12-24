//
//  main.c
//  格式化读写
//
//  Created by LongHu on 2020/12/15
//  Copyright © 2019 LongHu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 stdout:屏幕 标准输出文件
 stdin:键盘 标准输入文件
 自定义文件指针:自定义文件
 printf(”%s\t%d\t%d\n"，”HH“，12，13)
 
 fprintf(FILE * write,”%s\t%d\t%d\n"，”HH“，12，13);
 fscanf(FILE * read)
 */
struct student{
    char name[100];
    int age;
    char sex[100];
};


int main(int argc, const char * argv[]) {
    int studentNum = 0;
    printf("请输入学生数:\n");
    scanf("%d",&studentNum);
    struct student *array =(struct student *)malloc(sizeof(struct student)*studentNum);
    FILE *write = fopen("/Users/LongHu/Desktop/student.txt", "w");
    
    for (int i = 0; i<studentNum; i++) {
        printf("请输入第%d位学生的信息:",i+1);
        scanf("%s,%d,%s",array[i].name,&array[i].age,array[i].sex);
        fprintf(write, "%s\t%d\t%s\n",array[i].name,array[i].age,array[i].sex);
    }
    fclose(write);
    
    FILE *read = fopen("/Users/LongHu/Desktop/student.txt", "r");
    struct student temp;//临时的结构体来存储读出来的信息
    while (fscanf(read, "%s\t%d\t%s\n",temp.name,&temp.age,temp.sex) != EOF) {
        printf("%s\t%d\t%s\n",temp.name,temp.age,temp.sex);
    }
    
    fclose(read);
    
//    system("pause");
    
    /*
    fprintf(stdout,"%s\t%d\t%d\n","HH",12,13);
    int a;
    fscanf(stdin, "%d",&a);
    printf("a= %d\n",a);
     */
    
    return 0;
}
