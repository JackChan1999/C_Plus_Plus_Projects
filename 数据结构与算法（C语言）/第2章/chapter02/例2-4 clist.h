#ifndef _CLIST_H_
#define _CLIST_H_

struct Node;
typedef struct Head*  pHead;  //头结点类型
typedef struct Node*  pNode;  //数据结点类型
//定义头结点
struct Head
{
	int length;
	pNode next; //指向下一个结点的指针
};
//定义数据结点
struct Node
{
	int data;
	pNode next; //指向后继结点的指针
};
pHead ClistCreate();  //创建循环链表
int getLength(pHead ph); //获取循环链表的长度
int IsEmpty(pHead ph); //判断链表是否为空
int ClistInsert(pHead ph, int pos, int val); //在链表的pos位置插入元素val
void print(pHead ph); //打印循环链表中的元素

#endif
