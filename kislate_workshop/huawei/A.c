/*
Problem 1: IP 地址
Input file:
 Output file:
{
    char ip[16];
    unsigned int a, b, c, d;
    scanf("%s", ip);
    sscanf(ip, "%u.%u.%u.%u", &a, &b, &c, &d);
    printf("%08b%08b%08b%08b\n", a, b, c, d);
    return 0;
}
 Time limit:
 standard input
 standard output
 1 seconds
 Memory limit: 512 megabytes
 Problem Description
 IP 地址是计算机网络中非常重要的概念。IPV4 中，每台计算机被一个 32 位二进制数所
标识，这个32位二进制数就是这台计算机的IP地址。
但是，32位二进制数往往难以输入与记忆。通常，将该二进制数划分为4段，每段8位，并以
十进制数的形式写出，段之间由小数点分隔。例如，192.168.21.187表示了11000000101010000001010110111011。
现在，给出点分形式的IP地址，请输出其二进制形式。
Input
输入一行一个字符串，表示一个IP地址。
保证输入的IP地址合法。
Output
输出一行一个32位二进制数，表示二进制IP地址。
Examples
 Standard Input
 192.168.21.187
 Standard Output
 11000000101010000001010110111011
 Scoring
保证输入的IP地址合法
*/

#include<stdio.h>
void printBinary(int num) 
{
	unsigned int mask = 1 << 7; 
	for (int i = 0; i < 8; ++i) {
		printf("%d", (num & mask) ? 1 : 0); 
		mask >>= 1; 
	}
}
int main(void)
{
    char str[100];
    scanf("%s",str);
    int fst,scd,third,forth;
    sscanf(str,"%d.%d.%d.%d",fst,scd,third,forth);
    printBinary(fst);
    printBinary(scd);
    printBinary(third);
    printBinary(forth);
}
