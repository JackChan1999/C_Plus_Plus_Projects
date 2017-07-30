#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int getSum(int n)
{
	if (n == 1)
		return 1;
	int temp = getSum(n - 1); //调用自身
	return temp + n; //返回总和
}

int main()
{
	int sum;
	int n;
	printf("请输入n的值：\n");
	scanf("%d", &n);
	sum = getSum(n);
	printf("结果：%d\n",sum);

	system("pause");
	return 0;
}
