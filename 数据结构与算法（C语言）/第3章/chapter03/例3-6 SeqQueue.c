#include "SeqQueue.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

SeqQueue Create()
{
	SeqQueue Sq = (SeqQueue)malloc(sizeof(struct Queue)); //分配空间
	Sq->front = Sq->rear = -1;
	memset(Sq->data, 0, MAXSIZE*sizeof(int));
	return Sq;
}

int getLength(SeqQueue Sq)
{
	return Sq->rear - Sq->front; //队列长度是队头队尾之差
}

int IsEmpty(SeqQueue Sq)
{
	if (Sq->front = Sq->rear)//判断队列是否为空的条件
	{
		return 1;
	}
	return 0;
}

// 数组前边是队头, 后边是队尾
void Insert(SeqQueue Sq, int val)
{
	// 队列是否已满
	if (Sq->rear == MAXSIZE - 1)
	{
		printf("队列已满，无法再插入元素！\n");
		return;
	}
	//如果是空队列
	if (Sq->front == Sq->rear) 
	{
		Sq->front = Sq->rear = 0; 
		Sq->data[Sq->rear] = val;
		Sq->rear++;
	}
	else
	{
		Sq->data[Sq->rear] = val; //保存数据
		Sq->rear++;
	}
}

int Del(SeqQueue Sq)
{
	// 空队列
	if (Sq->front == Sq->rear) //队列为空的条件
	{
		printf("队列为空，无元素可弹！\n");
		return 10000; //返回错误标志
	}
	int temp = Sq->data[Sq->front];
	Sq->front++; //删除队头元素后，front向后移动
	return temp;
}

int GetHead(SeqQueue Sq)
{
	// 空队列
	if (Sq->front == Sq->rear)
	{
		printf("队列为空，无元素可取！\n");
		return 10000;
	}
	// 获取元素
	return  Sq->data[Sq->front];
}

void Clear(SeqQueue Sq)
{

	Sq->front = Sq->rear = -1;
	printf("队列已清空！\n");
}

void Destory(SeqQueue Sq)
{
	free(Sq);
	printf("队列已销毁!\n");
}
