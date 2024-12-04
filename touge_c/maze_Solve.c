#include<stdio.h>
int paths[50][100][100];
int maze[100][100];
int count = 0;
int left(int maze[][100], int map[][100], int r, int c)
{
	if (c>0&&maze[r][c - 1] != 0&&map[r][c-1]!=1)
		return 1;
	else
		return 0;
}
int up(int maze[][100], int map[][100], int r, int c)
{
	if (r>0&&maze[r-1][c] != 0 && map[r-1][c] != 1)
		return 1;
	else
		return 0;
}
int right(int maze[][100], int map[][100], int r, int c)
{
	if (c<100&&maze[r][c+1] != 0 && map[r][c+1] != 1)
		return 1;
	else
		return 0;
}
int down(int maze[][100], int map[][100], int r, int c)
{
	if (r<100&&maze[r+1][c] != 0 && map[r+1][c] != 1)
		return 1;
	else
		return 0;
}
int findWay(int maze[][100],int map[][100],int r,int c,int y,int x)
{
	map[y][x] = 1;
	if (x == c && y == r)
	{
		for (int i = 1;i <= r;i++)
		{
			for (int j = 1;j <= c;j++)
			{
				paths[count][i][j] = map[i][j];
			}
		}
		count++;
		map[y][x] = 0;
		return 1;
	}
	if (left(maze, map, y, x))
	{
		findWay(maze, map, r, c, y, x - 1);
	}
	if (right(maze, map, y, x))
	{
		findWay(maze, map, r, c, y , x+1);
	}
	if (up(maze, map,  y, x ))
	{
		findWay(maze, map, r, c, y - 1,x );
	}
	if (down(maze, map , y, x))
	{
		findWay(maze, map, r, c, y + 1, x);
	}
	map[y][x] = 0;
	return 0;
}
int main(void)
{
	int r, c;
	int x=1, y=1;
	scanf("%d%d", &r, &c);
	for (int i = 0;i < r + 2;i++)
	{
		for (int j = 0;j < c + 2;j++)
		{
			if (i == 0||i==r+1||j==0||j==c+1)
				maze[i][j] = 0;
			else
			{
				scanf("%d", &maze[i][j]);
			}
		}
	}
	int map[100][100] = { 0 };
	findWay(maze, map, r, c, 1, 1);
	if (count == 0)
	{
		printf("没有找到路径");
	}
	else
	{
		for (int i = 0;i < count;i++)
		{
			printf("%d\n", i + 1);
			for (int j = 1;j <= r;j++)
			{
				for (int k = 1;k <= c;k++)
				{
					printf("%d", paths[i][j][k]);
					if (k != c)
						putchar(' ');
				}
				putchar('\n');
			}
		}
	}
}
