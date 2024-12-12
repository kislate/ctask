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
//


//strcat()
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
//_strcat()



//strcmp()
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
//_strcmp()


//strcpy()
    strcpy(flower,"Rose");//这个函数可以把后面的字符串拷贝到前面的字符串中
    //这时候我们第一个参数不一定指向数组的开始，可以从中间开始拷贝
    //strcpy会把原字符串中的内容覆盖掉，然后把新的字符串拷贝进去，\0也会被拷贝进去
    const char *orig="beast";
    char copy[40]="Be the best that you can be.";
    char *ps;

    puts(orig);
    ps=strcpy(copy+7,orig);//这个函数会返回一个指向目标字符串的指针
    //这个函数会把orig的内容拷贝到copy的第7个字符开始的位置
    puts(copy);
    puts(ps);//这里会输出beast，因为'\0'会把‘that’的t给覆盖掉;

    strncpy(copy,"The worst",5);//这个函数会把copy的前5个字符替换成后面的字符串,
    //不会覆盖后面的字符，但是因为不会拷贝\0，所以一般设定的大小参数n一般比目标数组的大小少一
//_strcpy()

//sprintf()
    sprintf(flower,"A %s in the hand is worth %d in the bush.","bird",10);//这个函数可以把格式化的字符串存储到目标字符串中
    //这个函数会返回一个整数，表示存储的字符的数量
    //这个函数可以用来把数字转换成字符串
    //这个函数可以用来把字符串拼接到另一个字符串中
    //其实就是把printf打印的东西存储到一个字符串中


/*下面总结了一些其他字符串函数

    char *strchr(const char *str,int ch);
    //这个函数会在字符串中查找第一个出现的字符，然后返回一个指向该字符的指针
    //如果没有找到，就会返回一个空指针

    char *strrchr(const char *str,int ch);
    //这个函数会在字符串中查找最后一个出现的字符，然后返回一个指向该字符的指针
    //如果没有找到，就会返回一个空指针

    char *strstr(const char *str1,const char *str2);
    //这个函数会在字符串中查找第一个出现的str2字符串，然后返回一个指向该字符串的指针
    //如果没有找到，就会返回一个空指针
    
    char *strtok(char *str,const char *delim);
    //这个函数会把字符串分割成几个部分，然后返回第一个部分的指针
    //这个函数会把字符串中的分隔符替换成\0

    {
    char str[] = "Hello, world! This is a test.";
    const char delim[] = " ,.!"; // 分隔符：空格、逗号、点

    // 第一次调用 strtok，传递要分割的字符串
    char *token = strtok(str, delim);

    // 后续调用 strtok，传递 NULL
    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, delim);
    }
    
    size_t strspn(const char *str1,const char *str2);
    //这个函数会返回str1中第一个不在str2中的字符的位置
    //这个函数会返回一个整数，表示str1中第一个不在str2中的字符的位置，就是从0开始的
    //这个函数可以用来检查字符串中是否有非法字符
    
    size_t strcspn(const char *str1,const char *str2);
    //这个函数会返回str1中第一个在str2中的字符的位置
    //这个函数会返回一个整数，表示str1中第一个在str2中的字符的位置
    //这个函数可以用来检查字符串中是否有合法字符

    char *strpbrk(const char *str1,const char *str2);
    //这个函数会返回str1中第一个在str2中出现的字符的位置
    //这个函数会返回一个指向str1中第一个在str2中出现的字符的指针
    //这个函数可以用来检查字符串中是否有合法字符

    char *strlwr(char *str);
    //这个函数会把字符串中的大写字母转换成小写字母
    //这个函数会返回一个指向转换后的字符串的指针
    //这个函数会改变原字符串
    //这个函数只能用来转换字母
    
    char *strupr(char *str);
    //这个函数会把字符串中的小写字母转换成大写字母
    //这个函数会返回一个指向转换后的字符串的指针
    //这个函数会改变原字符串
    //这个函数只能用来转换字母

    char *strrev(char *str);
    //这个函数会把字符串中的字符的顺序反转

    char *strset(char *str,int ch);
    //这个函数会把字符串中的所有字符都设置成ch
    //这个函数会返回一个指向设置后的字符串的指针
    //这个函数会改变原字符串

    char *strnset(char *str,int ch,size_t n);
    //这个函数会把字符串中的前n个字符都设置成ch
    //这个函数会返回一个指向设置后的字符串的指针
    //这个函数会改变原字符串

    char *strerror(int errnum);
    //这个函数会返回一个指向错误信息的字符串的指针
    
    size_t strlen(const char *str);
    //这个函数会返回字符串的长度，不包括\0

    char *strdup(const char *str);
    //这个函数会返回一个指向str的副本的指针
    //这个函数会返回一个指向新字符串的指针

*/




}
//其实puts，fputs都是给他一个地址，然后往后遍历数据，
//所以你甚至可以加减这个地址来来改变开始打印的位置，但是不能乱打.jpg