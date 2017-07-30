#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include"list.h"

int main()
{
	int ret;
	pHead *ph = createList(); //创建链表
	if (ph == NULL)
	{
		printf("创建链表失败！\n");
	}
	int arr[10] = { 1, 2, 3, 4, 56, 76, 7, 4, 36, 34 }; //定义一个int类型数组

	for (int i = 0; i <= 6; i++)
	{
		Insert(ph, 0, arr[i]); //将数组元素插入到链表中，每次都从头部插入
	}

	printf("链表长度：%d\n", Size(ph));

	printf("打印链表中的元素：\n");
	print(ph);
	printf("删除链表中的元素，请输入要删除的元素：\n");
	int num;
	scanf("%d", &num); //本例中为测试程序，为减少异常处理，请输入链表中有的元素
	Delete(ph, num);
	printf("元素删除成功，删除元素%d后，链表中元素为：\n", num);
	print(ph);

	ret = find(ph, 3); //查找链表中某一个元素
	if (ret)
		printf("get!\n");
	else
		printf("NO!\n");

	system("pause");
	return 0;
}
