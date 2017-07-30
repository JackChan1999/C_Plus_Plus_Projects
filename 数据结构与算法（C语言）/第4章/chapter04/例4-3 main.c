#define _CRT_SECURE_NO_WARNINGS
#include "head.h"

int main()
{
	char s[1024], t[100];
	int next[100]; //存储t串的模式值
	printf("请输入主串s：\n");
	scanf("%s", s);
	printf("请输入模式t:\n");
	scanf("%s", t);
	printf("s长度：%d\n", strlen(s));
	printf("t长度：%d\n", strlen(t));

	printf("模式串t的next值：");
	get_Next(t, next);

	int ret = KMP(s, t, next);
	if (ret == -1)
		printf("匹配失败！\n");
	else
		printf("匹配成功，t串在s串中第一次出现的位置是%d\n", ret);

	system("pause");
	return 0;
}
