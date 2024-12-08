#include<stdio.h>
#define STLEN 14
int main(void)
{
    char *p1="Klingon";
    p1[1]='F';//不能直接更改，因为“Klingon”本身是指针，指向一个静态存储中字符串，
    //这个字符串可以被其他使用同样字符串的表达式使用，（优化程序），所以不能直接这么改。
    //用数组保存这玩意时，是先创建一个“Klingon"，然后再移到的数组里，
    //所以会有一个‘Klingon’的副本再静态存储空间中，常量区中。
    //那个副本会被所有和它相等的东西使用
    char *p2="Klingon";
     //这个地址有p1=p2;
    char str1="Klingon";
    char str2="Klingon";
   //这里可以知道，str1和str2用的是同一个副本
    printf("Kilngon");
    printf(":Beware the %ss","Klingon");

    char words[STLEN];
    puts("Enter a string .please.");
    fgets(words,STLEN,stdin);//当你输入的字符数量不大于STLEN时，你按了回车的话，'\n'也会被存储在其中
   
    puts(words);
    //输出的时候还会打出一个换行符,这个换行符不会加到words里边
    //所以如果你输入的fgets中有换行符的话就会换两次行

    fputs(words,stdout);
    //但是fputs不会给其加上换行符

    printf("%s",words);
    puts("Enter strings (empty line to quit:)");//fgets()返回的是一个指向char的指针，
  
    //正常的时候这个会返回输入的第一个参数的地址
    //但是读到文件结尾的时候，会返回空指针NULL,保证该指针不会指向任何有效数据。
    //出现某些错误的时候也会返回NULL;
    while(fgets(words,10,stdin)!=NULL && words[0]!='\0')//读到结尾或者空行
    {
        fputs(words,stdout);
    }
    puts("Done");
    //两函数的搭配使用

    int i=0;
    while(words[i] !='\n')
    {
        i++;
    }
    words[i]='\0';//可以用来处理掉换行符

    while (getchar()!='\n')
    {
        continue;
    }

        while(fgets(words,10,stdin)!=NULL && words[0]!='\0')//读到结尾或者空行
    {//fgets()会留一个位置给\0;
        i=0;
        while(words[i]!='\n' && words[i] !='\0')//一种情况，满了，另一种情况，没满（换行）
        {
            i++;
        }
        if(words[i]=='\n')
        {
            words[i]='\0';
        }//这里可以起到拼接字符串的作用
        else 
        {
            while (getchar()!='\n')//意味着你同一行内超出的部分都没了。
            {
                continue;
            }//会一直删掉后续输入直到遇到\n；
        }
        puts(words);//输入中的\n都已经被删掉了。
    }//其实就是我们习惯于换行结束输入，当我们结束输入时如果用了\n但是它应该结束却不结束的时候，就会把多余的输入删掉，
    //而且就算我们以\n结束了然后存储在里面以后把末尾的那个\n去掉
    puts("Done");//这里就是改良后的上面那串代码

    
    fputc('c',stdout);//这里是输出个字符；

    gets_s(words,10);//这个函数如果读到最大字符的时候还没有读到换行符
    //就会把目标数组的首字符设置为空字符，读取并丢弃随后的输入，然后返回空指针
    //我再vs试的时候会直接报错终止
    //不像fgets会读取'\n',而且默认的是stdin输入。


    char str2[10]={'H','e','l','l','o'};

    puts(str2);//这里会输出Hello，后面会一直输出乱码，因为没有、0程序会一直需寻找\0；

    char flower[80];
    char addon[]="s smell like old shoes.";
    puts("What is your favorite flower?");
    strcat(flower,addon);//这个函数会把addon的内容拼接到flower的后面
    puts(flower);
    puts(addon);//这个函数不会改变addon的内容

    int available=0;

    available=80-strlen(flower);//这个函数会返回字符串的长度，不包括\0
    //这里就可以计算剩余空间，这样就可以防止溢出。
    strncat(flower,addon,available);//这个函数只会最多拼接available个字符

    strcmp("kislate","kislate");//这个函数可以对比字符串
    //我们不能直接拿两个字符串的变量名来比较，因为他们代表的都是地址
    //我们可以用strcmp()函数来比较两个字符串，这个函数会返回一个整数
    //可以用来判断用户输入和期望值是否一样，而且可以用来排序，就是从首字母开始排序，直到不同或者一个字符串结束
    //这时候就会返回一个整数，如果是0，就是相等，如果是负数，就是第一个字符串小，如果是正数，就是第一个字符串大
    
    //这个函数是区分大小写的，如果不想区分大小写，可以用stricmp()函数

    stricmp("kislate","KISLATE");//==0;
    //在ASCII码中，大写字母的值小于小写字母的值，所以大写字母会排在小写字母前面
    //stricmp的比较方式是先把两个字符串的字母都转换成小写，然后再比较
    //非字母字符不会被转换，所以这个函数只能用来比较字母

    strncmp("kislate","kislate",3);
    //这个函数可以比较两个字符串的前n个字符，如果相等就返回0，如果不相等就返回一个整数
    //就是可以比较字符串的开头部分




}
//其实puts，fputs都是给他一个地址，然后往后遍历数据，
//所以你甚至可以加减这个地址来来改变开始打印的位置，但是不能乱打.jpg