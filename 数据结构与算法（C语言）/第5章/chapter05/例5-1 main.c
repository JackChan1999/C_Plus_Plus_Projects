#include <stdio.h> 
int main()
{
	//定义一个数组并初始化
	int a[2][3] = { 0, 1, 2, 3, 4, 5 };
	//地址输出
	int i = 0, j = 0;
	for (i; i < 2;i++)
	for (j; j < 3; j++)
		printf("%x\n", &a[i][j]);
	return 0;
}
