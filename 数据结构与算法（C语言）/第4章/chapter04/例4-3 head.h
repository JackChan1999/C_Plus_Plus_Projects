#include <stdio.h>
#include <stdlib.h>

void get_Next(char* t, int* next)
{
	//求模式串t的next值并存入数组next中
	int i = 0, j = -1;
	next[0] = -1;
	while (t[i] != '\0') //循环条件
	{
		if (j == -1 || t[i] == t[j])
		{
			i++, j++;
			if (t[i] != t[j])
				next[i] = j;
			else
				next[i] = next[j];
		}
		else
			j = next[j];
	}

	//将next值打印显示
	for (int n = 0; n < i; n++)
		printf("%d  ", next[n]);
	printf("\n");
}
int KMP(char* s, char* t, int next[])
{
	if (s == NULL || t == NULL)
		return -1;
	//先求算出主串s与模式串t的长度
	int len = 0;
	char* temp = t;
	while (*temp++ != '\0') //求t的长度
		len++;

	//开始模式匹配
	int i = 0, j = 0;
	while (s[i] != '\0' && t[j] != '\0') //循环条件
	{
		if (j == -1 || s[i] == t[j]) //如果j=-1或者两个字符相等，就比对后面的字符
			i++, j++;
		else
			j = next[j]; //i不变，j改变，消除了主串的回溯

		//如果j的值等于模式t的大小，则证明t已经匹配到末尾
		if (j == len)
			return i - len;
	}
	return -1;
}