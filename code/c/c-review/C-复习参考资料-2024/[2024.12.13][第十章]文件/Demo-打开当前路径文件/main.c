//
//  main.c
//  Demo-打开当前路径文件
//
//  Created by LongHu on 2021/12/21.
//  Copyright © 2021 LongHu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

/*
 把main.c文件复制到桌面
 终端：
 cat >12.in 写入内容到12.in文件夹中 ctrl+D结束
 more 12.in 查看
 <读入
 >写出
 */

int main(int argc, const char * argv[]) {
        
    FILE *fp = fopen("test.txt", "r");
    if (fp) {
        int num;
        fscanf(fp, "%d",&num);
        printf("%d\n",num);
        fclose(fp);
    }else{
        printf("文件无法打开!\n");
    }
     
    return 0;
}
