//
//  main.c
//  将filename文件中的内容在屏幕上显示出来
//
//  Created by LongHu on 2020/12/15
//  Copyright © 2019 LongHu. All rights reserved.
//

/*   将filename文件中的内容在屏幕上显示出来  */

#include <stdio.h>
#include <stdlib.h>

void mytype(const char *filename);

int main(int argc, const char * argv[]) {
    mytype("/Users/LongHu/Desktop/test_test.txt");
    return 0;
}

void mytype(const char *filename){
    char ch;
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("cannot open the file");
        exit(-1);
    }
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch); //puts
    }
}
