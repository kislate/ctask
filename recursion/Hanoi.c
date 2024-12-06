void Move(char src, char dest)
{
	// src表示的是起始位置，dest表示的是目标位置
	printf("盘子从%c柱子->%c柱子\n",src,dest);
}
void Plate_Move(int n, char A, char B, char C)
{
	if (n == 1)
	{
		Move(A, C);   //这里即递归停下来的地方，把最底下一层的盘子（n），移动到C柱上
	}
	else //这里下面都是在递归ing!!! （下面这三条语句其实都是在同步进行的）
	{
		Plate_Move(n-1,A,C,B);//当不只一个圆盘时，我们先将上面 （n -1）个圆盘 借助 C柱子  从 A 柱子移动到 B 柱子
		
		Move(A, C);      //A柱剩余一个圆盘，将剩下的一个圆盘从 A 移动到 C
		
		Plate_Move(n - 1, B, A, C);  //以A柱为中转站，把B柱上的圆盘放在C上。
	}

}
int main()
{
	int n = 0;
	scanf("%d", &n);
	Plate_Move(n, 'A', 'B', 'C');  //n为几个圆盘，A,B,C分别对应A，B，C三个柱子
	return 0;
}
