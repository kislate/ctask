//
//  main.c
//  练习-02 文件重定向
//
//  Created by LongHu on 2020/12/15
//  Copyright © 2019 LongHu. All rights reserved.
//

//C语言把所有的设备当做文件来处理
//文本文件:ASCII文件，每个字节存放一个字符的ASCII码
//二进制文件:数据按照其在内存中的存储形式原样存放
//键盘是个流式文件
/*
 标准输入：键盘  stdin
 标准输出:显示器 stdout
 标准出错输出:显示器 stderr
 
 */

#include <stdio.h>
#include <stdlib.h>

//int main1(int argc, const char * argv[]) {
//
//    char str[1024] = {0};
//    gets(str);
//    puts(str);
//    system(str);
//    return 0;
//}


int main(){
    char str[1024] = {0};
    fgets(str, 1024, stdin);//键盘就是一个特殊的文件，gets实际上是fgets的特殊形式
    fputs(str, stdout);//显示器也就是一个特殊的文件，puts是fputs的特殊形式
    system(str);
    return 0;
}

