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

