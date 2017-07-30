#include "LinkQueue.h"
#include <stdio.h>
#include <stdlib.h>

LQueue Create() //创建队列
{
	LQueue Lq = (LQueue)malloc(sizeof(struct Queue)); //为头结点分配空间
	Lq->front = NULL;
	Lq->rear = NULL;
	Lq->length = 0;
}

int getLength(LQueue Lq) //获取长度
{
	return Lq->length;
}

int IsEmpty(LQueue Lq) //判断是否为空
{
	if (Lq->length == 0)
		return 1;
	return 0;
}

void Insert(LQueue Lq, int val) //入队
{
	pNode pn = (pNode)malloc(sizeof(struct Node)); //为val值分配结点
	pn->data = val;
	pn->next = NULL;
		//如果队列为空,则将pn结点插入到头结点后
	if (IsEmpty(Lq)) 
	{
		//Lq->next = pn;
		Lq->front = pn; //front指向pn结点
		Lq->rear = pn; //rear指向pn结点
	}
	else //如果队列不为空
	{
		Lq->rear->next = pn; //插入到rear指针后
		Lq->rear = pn; //pn结点插入到rear位置处
	}
	Lq->length++;
}

int GetHead(LQueue Lq) // 获取队头元素
{
	if (IsEmpty(Lq))
	{
		printf("队列为空，无元素可取！\n");
		return 10000;
	}
	return Lq->front->data;
}

pNode Del(LQueue Lq)  //出队
{
	if (IsEmpty(Lq))
	{
		printf("队列为空，删除错误！\n");
		return NULL;
	}
	pNode pTmp = Lq->front;
	Lq->front = pTmp->next;
	Lq->length--;
	return pTmp;
}

void Clear(LQueue Lq) // 将队列Lq清空
{
	//回到初始状态
	Lq->front = NULL;
	Lq->rear = NULL;
	Lq->length = 0;
	printf("队列已经清空！\n");
}
