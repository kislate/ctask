//
//  main.c
//  把键盘输入的内容存到磁盘
//
//  Created by LongHu on 2020/12/15
//  Copyright © 2019 LongHu. All rights reserved.
//

/*
 stdout:屏幕 标准输出文件
 stdin:键盘 标准输入文件
 自定义文件指针:自定义文件
 printf(”%s\t%d\t%d\n"，”HH“，12，13)
 
 fprintf(FILE * write,”%s\t%d\t%d\n"，”HH“，12，13);
 fscanf(FILE * read)
 */
#include <stdio.h>
#include <stdlib.h>
void mytype(const char *filename);
void copy_TERM(const char *filename);

int main(int argc, const char * argv[]) {
    //写入函数 使用 Ctrl + Q 和 Ctrl +D 结束输入
    copy_TERM("/Users/LongHu/Desktop/test_test.txt");
    //读取函数
    mytype("/Users/LongHu/Desktop/test_test.txt");
    return 0;
}

void copy_TERM(const char *filename){
    FILE *fp;
    char ch;
    if ((fp = fopen(filename,"w")) == NULL) {
        printf("cannot open the File!\n");
        exit(-1);
    }
    while ((ch = getchar()) != EOF) {
        fputc(ch,fp);
    }
    fclose(fp);
}


void mytype(const char *filename){
    char ch;
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("cannot open the file");
        exit(-1);
    }
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }
    
}
