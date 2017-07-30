#ifndef _LINKQUEUE_H
#define _LINKQUEUE_H

typedef struct Node * pNode;
typedef struct Queue * LQueue; //相当于定义头结点pHead
struct Node
{
int data; //数据域
pNode next; //指针域
};

struct Queue //头结点
{
	pNode front; //指向头结点，相当于链表中头结点里的next指针
	pNode rear;  //指向尾结点
	int length; //队列长度
};

LQueue Create(); //创建队列
int getLength(LQueue Lq); //获取长度
int IsEmpty(LQueue Lq); //判断是否为空
void Insert(LQueue Lq, int val);// val元素入队
int GetHead(LQueue Lq);// 获取队头元素
pNode Del(LQueue Lq);// 出队
void Clear(LQueue Lq);// 将队列Lq清空
#endif	//_LINKQUEUE_H
