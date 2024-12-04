#include<stdio.h>
#define STLEN 10
int main(void)
{
    char words[STLEN];
    gets(words);
    puts(words);
    printf("%s\n",words);
    fputs("Done",stdout);
}