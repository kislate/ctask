//16.小 S 与 NLP
// 【题目描述】
// 小 S 是一位世界记录员，她的职责是将来自不同异世界的文字材料整理归档。
// 虽然异世界的文明不知道为何都是用日语交流，但是他们的文字各异。所以处理这
// 些材料并非易事。
// 幸好小 S 是一位 NLP（自然语言处理）高手，通过机器学习，她的模型帮她轻松
// 地把所有文本翻译成了英文。
// 但是小 S 发现，她的语言模型不能很好的处理不同进制数值的转换，所以她只好进
// 行人脑 NLP，手动完成异世界数字文本的替换工作。
// 幸好，小 S 有一份巨大的字典，其中包含 n 个异世界数字代表的数值。她只需要单
// 纯的依此对翻译后的英文文本进行简单替换即可。
// 不过由于小 S 正在用电脑玩肉鸽游戏 tarjan lusa，无法使用，所以这项任务就被丢
// 给了你。
// 为了方便本世界的计算机处理，需要进行替换的异世界数字都被替换成了小写英
// 文字符串，并处于 {} 之间。简单的说，你需要把给出的英文文本里每一句话中全部的
// {异世界数字} 替换为变量的值并输出。同时小 S 保证，给你的每句话都满足仅由大小
// 写英文字母、空格、半角逗号、半角句号和 {、} 组成。同时每句话由在 {} 之间的，必
// 然为字典中 N 个异世界数字中的一个。
// 例如，有 a = 20, b = 10，对于句子 Kitsuki achieved a {b} game winning
// streak on advanced difficulty of {a}.，替换后将得到 Kitsuki achieved a
// 10 game winning streak on advanced difficulty of 20.。
// 【输入格式】
// 输入共 n + m + 1 行。
// 输入的第一行为两个整数 n, m。
// 接下来 n 行，每行一个小写英文字符串、一个整数，分别代表异世界数字和其代表
// 的数值。
// 接下来 m 行，每行一个需要进行替换的句子。
// 【输出格式】
// 输出 m 行，每行一个标注好的句子。
// 【样例 1 输入】
// 1 4 2
// 2 shinki 1
// 3 a 3
// 4 tarjanlusa 4
// 5 d 5
// 6 We have {a} apples.
// 7 We {d}onot have pencils.
// 【样例 1 输出】
// 1 We have 3 apples.
// 2 We 5onot have pencils.
// 【子任务】
// 对于 100% 的测试数据，1 ≤ n ≤ 5000，1 ≤ m ≤ 20。保证 {} 成对合法出现，需要
// 替换的句子长度不超过 5 × 104。异世界数字为长度不超过 20 的英文小写字母串，且对
// 应的数值在 int 范围内。每句话由大小写英文字母、空格、半角逗号、半角句号和 {、}
// 组成。
// 【提示】
// string 类型是 C++ 提供的有力类型，它封装了很多常用的字符串成员函数。
// cin/cout 是 C++ 风格的输入方式，它在读取字符串时尤其好用。
// 本题使用字符数组同样方便，但在后面的题目中，你可以尝试学习并使用上面提示
// 的内容，并选择自己喜欢的那个。
// 我们计划为你提供 string 类型的学习材料，有关内容正在编写中。
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
	char key[21];
	int value;
} dict;
int main()
{
	char c;
	int m,n;
	scanf("%d %d",&n,&m);
	dict *s=(dict *)malloc(n*sizeof(dict));
	char line[m][50001];
	//录入异世界数据 
	for(int i=0;i<n;i++) scanf("%s %d",s[i].key,&s[i].value);
	getchar();//除换行符 
	//边输入语句边改值
	for(int j=0;j<m;j++)
	{
		int k=0,r=0;
		while((c=getchar())!='\n')
		{
			if(c!='{') line[j][k++]=c;
			else {
				char bi[21]={0};
				char temp[15]={0};
				while((c=getchar())!='}')
					bi[r++]=c;
				for(int i=0;i<n;i++)
						if (strcmp(bi,s[i].key) == 0)
							{
								sprintf(temp, "%d", s[i].value); //将数值转换为对应的字符形式 
								strcat(line[j], temp);
								k+=strlen(temp);
							}
				r=0;
			}
		}
		k=0;
	}
	//打印输出
	for(int i=0;i<m;i++)
	{
		printf("%s",line[i]);
		if(i<m-1)
			printf("\n");
	}
	free(s);
} 
//洛谷测评三色俱全？？？
//不知道哪里出了问题
