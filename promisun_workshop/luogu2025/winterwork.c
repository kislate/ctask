//1.小L在吃饭
#include<stdio.h>
int main()
{
	int a,b,n=0;
	scanf("%d %d",&a,&b);
	if(a<=10000&&a>=0&&b>=0&&b<=9)
	{
		n=(10*a+b)/19;
		printf("%d",n);
	}
	else printf("钱数错误");
	return 0; 
} 


//2.小 W 在游泳
#include<stdio.h>
int main()
{
	float a,b,sum=0;
	int n=0;
	scanf("%f",&a);
	b=2;
	while(sum<a)
	{
		sum+=b;
		b*=0.98;
		n++;
	}
	printf("%d",n);
	return 0; 
} 


//3.小 C 在上课
#include<stdio.h>
int main()
{
	int a,b,c,res;
	scanf("%d %d %d",&a,&b,&c);
	res=0.2*a+0.3*b+0.5*c;
	printf("%d",res);
	return 0; 
} 


//4.好数
#include<stdio.h>
int main()
{
	int x,a=0,b=0;
	scanf("%d",&x);
	if(!(x%2))a=1;
	if(x>4&&x<=12)b=1;
	if(a&&b) printf("1 ");
	else printf("0 ");
	if(a||b) printf("1 ");
	else printf("0 ");
	if(a&&!b||!a&&b) printf("1 ");
	else printf("0 ");
	if(!a && !b) printf("1");
	else printf("0");
	return 0; 
} 


//5.排序
#include<stdio.h>
int main()
{
	int a,b,c,d;
	scanf("%d %d %d",&a,&b,&c); 
	if(a>b){
		d=a;a=b;b=d;
	}
	if(a>c){
		d=a;a=c;c=d;
	}
	if(b>c){
		d=b;b=c;c=d;
	}
	printf("%d %d %d",a,b,c); 
	return 0; 
} 


//6.谁更短
#include<stdio.h>
int main()
{
	int me,lz,n;
	scanf("%d",&n);
	me=5*n;
	lz=3*n+11;
	if(me<lz) printf("Local");
	else printf("Luogu");
	return 0; 
} 


//7.倍减
#include<stdio.h>
int main()
{
	long x;
	int i=1;
	scanf("%ld",&x);
	while(x=x/2) i++;
	printf("%d",i);
	return 0; 
} 


//8.有说服力的评分算法
#include<stdio.h>
#include<stdlib.h>
int main()
{
	int n,sum=0,max=0,min=10;
	scanf("%d",&n);
	int *s=(int *)malloc(n*sizeof(int));//动态分配
    for(int i=0;i<n;i++)
	{
		scanf("%d",&s[i]);
		if(s[i]>max) max=s[i];
		if(s[i]<min) min=s[i];
		sum+=s[i];
	}
	free(s);
	sum=sum-max-min;
	printf("%.2f",1.00*sum/(n-2));
	return 0; 
} 


//9.多项式筛素数
#include<stdio.h>
int isPrime(int n){
 	 for(int i=2,j=n>>1;i<=j;++i){
	    if(!(n%i)) return 0;
	}
	return 1;
}
int main()
{
	int sum=0,n=0,S,i=2;
	scanf("%d",&S);
	while(sum<S){
		while(!isPrime(i))i++;
		sum+=i;
		if(sum<=S){
			printf("%d\n",i);
			i++;n++;
		}
	}
	printf("%d",n);
	return 0; 
} 


//10.数位枚举
#include<stdio.h>
int main()
{
	int n,x,count=0;
	scanf("%d %d",&n,&x);
	for(int i=1;i<=n;i++)
	{
		int j=i;
		while(j){
			if(j%10==x) count++;
			j/=10;
		}
	}
	printf("%d",count);
	return 0; 
} 


//11.阅读论文
#include<stdio.h>
#include<stdlib.h>
int main()
{
	int page,book,data,flag=0,index=0,count=0;
	scanf("%d %d",&page,&book);
	int *s=(int *)malloc(page*sizeof(int));//动态分配
	for(int i=0;i<page;i++) s[i]=-1;//初始化 
	for(int i=0;i<book;i++)
	{
		scanf("%d",&data);
		for(int i=0;i<page;i++)
			if(s[i]==data) flag=1;//找到 
		if(flag==0) 
		{
			s[index++]=data;
			count++;
		}
		if(index==page) index=0;//满页复位 
		flag=0;
	}
	free(s);//释放 
	printf("%d",count);
	return 0; 
} 


//12.在线购物
#include<stdio.h>
#include<stdlib.h>
int main()
{
	int good,consu,length;
	long code,min=10000000,chu=1;
	scanf("%d %d",&good,&consu);
	//动态分配与初始化 
	long *s=(long *)malloc(good*sizeof(long));
	long *t=(long *)malloc(consu*sizeof(long));
	for(int n=0;n<consu;n++) t[n]=-1;
	//输入商品信息 
	for(int i=0;i<good;i++) scanf("%ld",&s[i]); 
	//了解客户需求
	for(int j=0;j<consu;j++)
	{
		scanf("%d %ld",&length,&code);
		for(int m=0;m<length;m++) chu*=10;
		//找商品
		for(int i=0;i<good;i++)
			if(s[i]>=code)
				if((s[i]-code)%chu==0&&s[i]<min)
				{
					min=s[i];
					t[j]=min;
				}
		//归位 
		min=10000000;
		chu=1;
	} 
	//打印结果
	for(int i=0;i<consu;i++) printf("%ld\n",t[i]);
	free(s);//释放 
	free(t);
	return 0; 
}


//13.lhm 玩 01
#include<stdio.h>
#include<stdlib.h>
int main()
{
	int N,count=0,reset=0,put=0,he=0;
	scanf("%d",&N);
	reset=N;
	int *s=(int *)malloc(N*N*sizeof(int));
	do{
		scanf("%d",&s[count]);
		he+=s[count++];
	}
	while(he<N*N);
	for(int i=0;i<count;i++,put++)
		for(int j=0;j<s[i];j++)
		{
			if(put%2==0) printf("0");
			else printf("1"); 
			reset++;
			if(reset%N==0&&reset<=(N*N)) {
				printf("\n");
			}
		}
	free(s);
	return 0; 
} 


//14.bngg 与 hmgg 的决斗
#include<stdio.h>
#include<stdlib.h>
int main()
{
	int n,m,p1,p2;
	long long s1,s2,bn=0,hm=0,cha=0;
	scanf("%d",&n);
	//战场士兵 
	long long *c=(long long *)malloc(n*sizeof(long long));
	for(int i=0;i<n;i++)
		scanf("%lld",&c[i]);
	//奇袭 
	scanf("%d %d %lld %lld",&m,&p1,&s1,&s2);
	c[p1-1]+=s1;
	for(int i=0;i<m-1;i++) bn=bn+c[i]*(m-1-i);
	for(int i=m;i<n;i++) hm=hm+c[i]*(i-m+1);
	//派遣
	cha=llabs(bn-hm);//派到m战场 
	p2=m-1;
	for(int j=0;j<n;j++)
	{
		if(j<m-1) bn=bn+s2*(m-1-j);
		if(j>m-1) hm=hm+s2*(j-m+1);
		if(llabs(bn-hm)<cha)
		{
			cha=llabs(bn-hm);
			p2=j;
		}
		//归位 
		if(j<m-1) bn=bn-s2*(m-1-j);
		if(j>m-1) hm=hm-s2*(j-m+1);
	} 
	p2++;
	printf("%d",p2);
	free(c);
	return 0; 
} 


//15.lhm 玩数字
#include<stdio.h>
#include<stdlib.h>                          
void selectSort(int *arr,int n){
    for(int i=0;i<n;i++){
    	for(int j=i+1;j<n;j++){
    		if(arr[i]>arr[j]){
    			int t=arr[i];
    			arr[i]=arr[j];
    			arr[j]=t;
			}
		}
	}
}
int main()
{
	int n,k,j=1,res,find=0;
	scanf("%d %d",&n,&k);
	int *s=(int *)malloc(n*sizeof(int));
	for(int i=0;i<n;i++)
		scanf("%d",&s[i]);
	selectSort(s,n);
	res=s[0];
	for(int i=0;i<n;i++)
	{
		if(s[i]>res) 
		{
			res=s[i];
			j++;
		}
		if(j==k) {
			find=1;
			break;
		}
	}
	if(find) printf("%d",res);
	else printf("NO RESULT");
	free(s);
	return 0; 
} 


//16.小 S 与 NLP
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



//17.小 S 与时间逆流
#include <stdio.h>
#include <string.h>
void reverse(char *str, int l, int r) {
    while (l < r) {
        char temp = str[l];
        str[l] = str[r];
        str[r] = temp;
        l++;
        r--;
    }
}
void find(char *S) {
    int n = strlen(S);
    char minT[101]; // 存储字典序最小的结果
    strcpy(minT, S); // 初始化为原字符串
    for (int l = 0; l < n; l++) {
        for (int r = l; r < n; r++) {
            char T[101]; // 存储当前翻转后的字符串
            strcpy(T, S); // 复制原字符串到 T
            // 翻转区间 [l, r]
            reverse(T, l, r);
            // 比较字典序，更新最小的 T
            if (strcmp(T, minT) < 0) {
                strcpy(minT, T);
            }
        }
    }
    // 输出结果
    printf("%s", minT);
}
int main() {
    char S[101]; // 输入字符串
    scanf("%s", S); // 读取输入
    find(S); // 处理并输出结果
    return 0;
}



//18.小 S 与历史长河
#include<stdio.h>
#include<string.h>
#include<stdlib.h>  
int main()
{
	char s[1001]={0},t[1001]={0};
	int count=0,ls,rs,lt,rt; 
	
	scanf("%s",s);
	scanf("%s",t);
	scanf("%d",&count);
	char **result=(char**)malloc(count*sizeof(char*));
	for(int i=0;i<count;i++)
		result[i]=(char*)malloc(8*sizeof(char));
	//处理 
	for(int i=0;i<count;i++)
	{
		char S[1001]={0},T[1001]={0};
		scanf("%d %d %d %d",&ls,&rs,&lt,&rt);
		
		for(int m=ls-1,p=0;m<rs;m++) S[p++]=s[m];
		for(int n=lt-1,q=0;n<rt;n++) T[q++]=t[n];
		
		if(strcmp(S,T)<0) result[i]="yifusuyi";
		if(strcmp(S,T)>0) result[i]="erfusuer";
		if(strcmp(S,T)==0) result[i]="ovo";
	}
	//打印结果
	for(int i=0;i<count;i++)
		{
			printf("%s",result[i]);
			if(i<(count-1))
				printf("\n");
		}
	for (int i=0;i<count;i++) {
        free(result[i]);
    }
    free(result);
	return 0; 
} //全是紫色，free有问题吗？