#include <stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>
#include "mystdio.h"

long fac(int n)
{
	long m=1;
    for(int i=1;i<=n;i++){
        m*=i;
    }
    return m;
}

long sum_fac(int n)
{
	long m=1;
    for(int i=1;i<=n;i++){
        m*=i;
    }
    return sum_fac(n-1)+m;
}

int isPrime(int n){
 	 for(int i=2,j=n>>1;i<=j;++i){
	    if(!(n%i)) return 0;
	}
	return 1;
}

int gcd(int a, int b)
{
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

int lcm(int a, int b){
    if (b == 0 || a==0) {
        return 0;
    }else return a*b/gcd(a,b);
}

long fibonacci(int n)
{
    long c[100];
    long F1=1,F2=1;
 	for(int i=0;i<=n-1;i+=2)
 	{
 		c[i]=F1;
 		F1+=F2;
 		c[i+1]=F2;
 		F2+=F1;
	}
    return c[n-1];
}

int isLeapyear(int n)
{
    if(!(n%400) || (!(n%4)&&(n%100))) return 1;
    else return 0;
}

int combination(int i,int j)
{ 
	int x=1,y=1;
	if(!j) return 1;
	for(int m=j;m>=1;m--)x*=m;
	for(int n=1;n<=j;i--,n++)y*=i; 
	return y/x;
}

void swap(int *a,int *b)
{
	int t;
	t=*a;
	*a=*b;
	*b=t;
}

char swapLetter(char c)
{
    if(c>='A'&&c<='Z') c=c-'A'+'a';
	else if(c>='a'&&c<='z') c=c-'a'+'A';
    return c;
}

void selectSort(int arr[],int n){
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

void outArray(int arr[],int n){
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}

void myrever(void)
{
	char c;
    c=getchar();
    if(c!='\n') 
	{
		myrever();
    	putchar(c);
	}
}

void bubble_sort(int arr[],int n){
    int *p=arr;
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (p[j] > p[j+1]) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void strnins(char *t,char *s,int n)
{
	int lent = strlen(t);
	int lens = strlen(s);
	for(int i=lent-1,j=i+lens;i>=n;i--,j--)
	{
		t[j]=t[i];
	}
	for(int i=n,j=0;j<lens;i++,j++)
	{
		t[i]=s[j];
	}
}

void strcate(char t[],char s[])
{
    int i=0,j=0;
    while(t[i++]);
    i=i-1;
    while((t[i++]=s[j++])!=0);
}

void strdelc(char s[],char c)
{
    static int k;
    int j;
    for(j=k=0;s[j]!=0;j++){
        if(s[j]!=c) s[k++]=s[j];
    }
    for(;s[k]!=0;k++) s[k]=0;
}

int isPalindrome(char arr[],int len){
    static int i=0;
    if(i>=len) return 1;
    if(arr[i]!=arr[len-1]) return 0;
    i++;
    return isPalindrome(arr,len-1);
}

void move(int u[],int n,int k){
    for(int i=0,j=n;i<k;i++,j++) {
    	u[j]=u[i];
	}
	for(int i=k,j=0;i<n;i++,j++){
		u[j]=u[i];
	}
	for(int i=n-k,j=n;i<n;i++,j++){
		u[i]=u[j];
	}
}

int divideFindLeft(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;
    int result = -1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            result = mid; // 更新结果为当前索引
            high = mid - 1; // 继续在左半部分查找
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

int divideFindRight(int arr[], int size, int target) {
    int low = 0;
    int high = size - 1;
    int result = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            result = mid; // 更新结果为当前索引
            low = mid + 1; // 继续在右半部分查找
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

void divideFind(int arr[], int size, int target) {
    int first = divideFindLeft(arr, size, target);
    int last = divideFindRight(arr, size, target);

    if (first == -1 || last == -1) {
        printf("Element not found\n");
    } else {
        printf("Element found from index %d to %d\n", first, last);
    }
}