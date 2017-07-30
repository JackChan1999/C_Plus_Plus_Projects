#ifndef _DLIST_H_
#define _DLIST_H_

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
	pNode pre; //指向前驱结点的指针
	pNode next; //指向后继结点的指针
};

pHead DlistCreate();  //创建双向链表
int getLength(pHead ph); //获取双向链表的长度
int IsEmpty(pHead ph); //判断链表是否为空
int DlistInsert(pHead ph, int pos, int val); //在链表的pos位置插入元素val
pNode DlistDelete(pHead ph, int val); //删除双向链表ph中的元素val
pNode DlistFind(pHead ph, int val); //查找双向链表中是否有值为val的元素
void DlistDestory(pHead ph); //销毁链表
void printFront(pHead ph); //打印双向链表中的元素
void printLast(pHead ph);
#endif
