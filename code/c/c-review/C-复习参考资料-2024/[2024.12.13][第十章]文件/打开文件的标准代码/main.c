//
//  main.c
//  打开文件的标准代码
//
//  Created by LongHu on 2020/12/24.
//  Copyright © 2020 LongHu. All rights reserved.
//
/*
         FILE *fp = fopen("file","r") //file 为文件的路径，r为read
         if(fp){ //返回是否是NULL，如果是NULL，文件无法打开
            fscanf(fp,...); //读文件
            fclose(fp);
         }else{
         
         }
 */

#include <stdio.h>
#include <stdlib.h>
void mytype(const char *filename);

int main(int argc, const char * argv[]) {
    
    
    FILE *fp = fopen("/Users/LongHu/Desktop/test.txt", "r");
    if (fp) {
        int num;
        fscanf(fp, "%d",&num);
        printf("%d\n",num);
        fclose(fp);
    }else{
        printf("文件无法打开!\n");
    }
     
    mytype("/Users/LongHu/Desktop/test_test.txt");
    return 0;
}

void mytype(const char *filename){
    char ch;
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("cannot open the file\n");
        exit(-1);
    }
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
        
    }
    fclose(fp);
    printf("\n");
    
}
