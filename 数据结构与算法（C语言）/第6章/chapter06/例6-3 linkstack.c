#include "linkstack.h"
#include <stdio.h>
#include <stdlib.h>

LinkStack Create() //创建栈
{
	LinkStack lstack = (LinkStack)malloc(sizeof(struct Stack));
	if (lstack != NULL)
	{
		lstack->top = NULL;
		lstack->size = 0;
	}
	return lstack;
}

int IsEmpty(LinkStack lstack) //判断栈是否为空
{
	if (lstack->top == NULL || lstack->size == 0)
		return 1;
	return 0;
}

int Push(LinkStack lstack, BitNode* val)
{
	pNode node = (pNode)malloc(sizeof(struct Node)); //为元素val分配结点
	if (node != NULL)
	{
		node->data = val;
		node->next = getTop(lstack); //新元素结点指向下一个结点,链式实现
		lstack->top = node; //top指向新结点
		lstack->size++;
	}
	return 1;
}

pNode getTop(LinkStack lstack) //获取栈顶元素
{
	if (lstack->size != 0)
		return lstack->top;
	return NULL;
}

pNode Pop(LinkStack lstack) //弹出栈顶元素
{
	if (IsEmpty(lstack))
	{
		return NULL;
	}
	pNode node = lstack->top; //node指向栈顶元素
	lstack->top = lstack->top->next; //top指向下一个元素
	lstack->size--;
	return node;
}
