#define _CRT_SECURE_NO_WARNINGS
#include "dlist.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
	//创建一个双向链表
	pHead ph = NULL;
	ph = DlistCreate();

	//向链表中插入元素
	int num;
	printf("请输入要插入的元素，输入0结束：\n");
	while (1)
	{
		scanf("%d", &num);
		if (num == 0)
			break;
		DlistInsert(ph, 0, num); //本测试程序从头部插入
	}

	printf("双链表长度：%d\n", getLength(ph));
	printFront(ph); //从前往后打印双链表的元素
	DlistInsert(ph, 3, 99); //在3位置插入新元素99
	printFront(ph);//然后再从前往后打印双链表的元素
	printLast(ph); //从后往前打印元素

	int val;
	printf("请输入要查找的元素：\n");
	scanf("%d", &val);
	DlistFind(ph, val); //查找元素

	int del;
	printf("请输入要删除的元素：\n");
	scanf("%d", &del);
	DlistDelete(ph, del); //删除元素
	printFront(ph); //打印删除元素后的链表

	DlistDestory(ph); //销毁链表
	printf("双链表销毁成功！\n此时链表长度为：%d\n", ph->length);

	system("pause");
	return 0;
}
