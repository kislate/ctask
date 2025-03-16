#include <stdio.h>
#include <limits.h>
#include <math.h>
int suanfa(int a[],int n, int arrsize)
{
/**********begin**********/
    if(n > arrsize)
    {
        printf("Error\n");
        return;
    }
    int factorial = 1;
    long long temp;
    for(int i = 1; i <= n; i++)
    {
        factorial *= i;
        temp = factorial * pow(2, i);
        if(temp > INT_MAX)
        {
            printf("Error\n");
            return;
        }
        
        a[i - 1] = factorial * pow(2, i);
    }
/**********end**********/
}