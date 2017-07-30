#define _CRT_SECURE_NO_WARNINGS
#include "clist.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int m, n;
	printf("请输入约瑟夫环的总人数：\n");
	scanf("%d", &m);
	if (m <= 0)
	{
		printf("请输入正确的数字！\n");
		return 0;
	}
	printf("请输入出局者的报数：\n");
	scanf("%d", &n);
	if (n <= 0)
	{
		printf("请输入正确的数字！\n");
		return 0;
	}

	//根据输入的m创建链表
	pHead ph = NULL;
	ph = ClistCreate();
	if (ph == NULL)
	{
		printf("创建循环链表失败！\n");
		return 0;
	}

	//插入元素
	for (int i = m; i > 0; i--)
	{
		ClistInsert(ph, 0, i); //使用头插法从m到1倒序插入
	}

	print(ph);
	printf("出局顺序：\n");
	//插入元素后，就循环遍历链表
	pNode node = ph->next; //node指针指向第一个结点
	while (node->next != node) //循环结束条件，结点指向其自身，此时剩最后一个结点
	{
		for (int i = 1; i < n - 1; i++) //i < n - 1，报到n就重新开始
		{
			node = node->next; 
		}
		//for循环结束后，node指针指向待出局的结点的前驱结点
		pNode pTmp = node->next; //pTmp指向要被踢出的结点
		
		//接下来先要判断这个结点是0号位置的结点还是其他位置的结点
		if (pTmp == ph->next) //如果此结点在0号位置
		{
			ph->next = pTmp->next; //头结点也要作处理
			node->next = pTmp->next;
			printf("%d  ", pTmp->data);
			free(pTmp);
			ph->length--;
		}
		else  //如果此结点在其他位置
		{
			node->next = pTmp->next;
			printf("%d  ", pTmp->data);
			free(pTmp);
			ph->length--;
		}
		node = node->next;
	}
	node->next = node;  //循环结束，只剩下node一个结点，让其指向自身
	printf("\n");

	printf("链表中最后留下的是 ");
	print(ph);

	system("pause");
	return 0;
}
