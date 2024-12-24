//
//  main.c
//  练习-01
//
//  Created by LongHu on 2020/12/15.
//  Copyright © 2019 LongHu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(){
    
    FILE *pf = fopen("/Users/LongHu/Desktop/test_test01.txt", "a");
    
    fputs("Hello World!", pf);//写入缓冲区
    
    fclose(pf);//关闭文件的时候，将缓冲区的内容写入文本
    return 0;
    
}

