#define _CRT_SECURE_NO_WARNINGS
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main()
{
	String s;
	char arr[1024];
	printf("请输入要赋值给s的串：\n");
	scanf("%s", arr);
	strAssign(&s, arr);

	printf("s:");
	print(&s);

	printf("长度：%d\n", strLength(&s));

	//再创建一个串t，来比较两个串的大小
	String t;
	printf("请输入要赋值给t的串：\n");
	scanf("%s", arr);
	strAssign(&t, arr);
	printf("t:");
	print(&t);
	printf("长度：%d\n", strLength(&t));

	printf("判断两个串是否相等：");
	strEqual(&s, &t);
	
	printf("比较两个串大小：");
	int ret = strCompete(&s, &t); //比较大小
	if (ret < 0)
		printf("串t较大！\n");
	if (ret == 0)
		printf("两个串一样大！\n");
	if (ret > 0)
		printf("串s较大！\n");

	//将两个串连接起来
	printf("将串s与t连接起来：");
	strConnect(&s, &t); //返回值为char*类型
	print(&s);
	printf("连接两个串后，s的长度：%d\n", strLength(&s));
	//将串s复制到串t中
	//strCopy(&s, &t); //将串t复制到串s中
	//printf("将串t复制到串s，则串s的值：");
	//print(&s);

	//在串s中插入一个串
	printf("请输入要插入的子串：\n");
	scanf("%s", arr);
	Insert(&s, 3, arr);
	printf("插入串后，s的长度：%d\n", strLength(&s));

	//删除串s中的某一个子串
	Delete(&s, 3, 5);
	printf("删除子串后，s的长度：%d\n", strLength(&s));

	system("pause");
	return 0;
}
