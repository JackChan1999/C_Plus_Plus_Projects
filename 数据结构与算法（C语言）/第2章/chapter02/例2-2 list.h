#ifndef _LIST_H_
#define _LIST_H_

struct Node;
typedef struct Node  List;
typedef struct Header pHead;

pHead * createList(); //创建链表
int isEmpty(pHead* l);  //判断链表是否为空
int Insert(pHead* l, int pos, int val); //插入元素，插入成功返回1；
List* Delete(pHead* l, int ele);  //删除元素，删除成功，返回删除的元素
List* find(pHead* l, int ele);  //查找某个元素是否存在
int Size(pHead* l);  //获取链表大小
void Destory(pHead* l); //销毁链表
void print(pHead *l); //打印链表

struct Node  //结点
{
	int data; //数据域
	struct Node* next;  //指向下一个结点的指针
};

struct Header  //头结点
{
	int length; //记录链表大小
	struct Node* next;
};
#endif
