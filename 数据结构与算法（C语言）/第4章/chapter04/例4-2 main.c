#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find(char* s, char* t) //模式匹配算法
{
	int i = 0, j = 0;
	while (i < strlen(s) && j < strlen(t))
	{
		if (s[i] == t[j]) //如果两个字符相等，则比对后续字符
		{
			i++;
			j++;
		}
		else //如果两个字符不相等
		{
			i = i - j + 1; //主串从下一个位置开始
              j = 0; //模式t从头开始
		}
	}
	//循环结束后，要查看i与j的位置
	if (j == strlen(t)) //如果j的值等于模式t的长度，则说明t已完全匹配
		return i - strlen(t); 
	else
		return -1;
}


int main()
{
	char s[1024], t[100];
	printf("请输入主串s：\n");
	scanf("%s", s);
	printf("请输入模式t:\n");
	scanf("%s", t);
	printf("s长度：%d\n", strlen(s));
	printf("t长度：%d\n", strlen(t));

	int ret = find(s, t);
	if (ret == -1)
		printf("匹配失败！\n");
	else
		printf("匹配成功，t串在s串中第一次出现的位置是%d\n", ret);

	system("pause");
	return 0;
}
