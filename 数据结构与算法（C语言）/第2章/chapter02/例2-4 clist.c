#include "clist.h"
#include <stdio.h>
#include <stdlib.h>

pHead ClistCreate() //创建循环链表
{
	pHead ph = (pHead)malloc(sizeof(struct Head)); //为头结点分配空间
	if (ph == NULL)
		printf("分配头结点失败！"); //为了方便运行结果查看，不设置return返回
	//创建好头结点后，初始化头结点中数据
	ph->length = 0;
	ph->next = NULL;
	return ph; //将头结点返回
}

int IsEmpty(pHead ph) //判断链表是否为空
{
	if (ph == NULL)
		printf("传入的双链表有误！");
	if (ph->length == 0) //如果长度为0，则链表为空
		return 1;
	else
		return 0;
}

int ClistInsert(pHead ph, int pos, int val) //在链表的pos位置插入元素val
{

	if (ph == NULL || pos < 0 || pos > ph->length)
	{
		printf("插入元素时，参数传入有误！\n");
	}

	pNode pval = NULL;
	//参数传入无误，则为新元素val分配结点
	pval = (pNode)malloc(sizeof(struct Node));
	pval->data = val; //将值val保存到此结点中

	//接下来要判断在哪个位置插入元素，先判断链表是否为空
	if (IsEmpty(ph)) //如果链表为空
	{
		ph->next = pval;  //直接将结点插入到头结点后
		pval->next = pval; //将第一个结点指向它自己
	}
	else //循环链表不为空，则分为在头部插入（即头结点后）和普通位置插入
	{
		pNode pRear = ph->next;
		if (pos == 0) //在第一个位置（头结点后）插入
		{
			//在0号位置插入，需要先找到尾结点
			while (pRear->next != ph->next) //循环结束的条件
			{
				pRear = pRear->next; //pCur指针向后移动
			}
			//while循环结束后，pRear指向尾结点
			//然后插入元素
			pval->next = ph->next;
			ph->next = pval;
			pRear->next = pval; //这三个步骤顺序不能更改
		}
		else //如果不是0号位置插入，则和单链表无区别
		{
			pNode pCur = ph->next;
			for (int i = 1; i < pos; i++) //就要遍历链表找到要插入的位置
			{
				pCur = pCur->next; //pCur指针向后移
			}
			//循环结束后，此时pCur指向的是要插入的位置
			pval->next = pCur->next; //指针断开再连接的过程
			pCur->next = pval;
		}
	}
	ph->length++;
	return 1;
}

void print(pHead ph) //打印循环链表中的元素
{
	if (ph == NULL || ph->length == 0)
	{
		printf("参数传入有误！");
	}

	pNode pTmp = ph->next;

	for (int i = 0; i < ph->length; i++)
	{
		printf("%d ", pTmp->data);
		pTmp = pTmp->next;
	}
	printf("\n");
}
