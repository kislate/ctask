//
//  main.c
//  printf 和 scanf的细节
//
//  Created by LongHu on 2020/12/15
//  Copyright © 2019 LongHu. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    
    int num;
    //Scanf 读入的项目数  Printf 输出的字符数,包含换行
    int i1 = scanf("%i",&num);
    int i2 = printf("%d\n",num);
    
    printf("%d:%d\n",i1,i2);
    
    
    return 0;
}
