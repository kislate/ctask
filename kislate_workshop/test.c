#include<stdio.h>
int main(void)
{
  int a[10],*p=a;
  while(p<a+10)
  {
    *++p=0;
  }
  return 0;
}