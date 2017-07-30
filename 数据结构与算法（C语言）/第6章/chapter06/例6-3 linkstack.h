#ifndef _LINKSTACK_H_
#define _LINKSTACK_H_

//二叉树的结点结构
typedef struct BitNode
{
	char data; //数据类型为char
	struct BitNode* lchild, *rchild;
}BitNode;

//栈的结点结构
typedef struct Node * pNode;
typedef struct Stack * LinkStack;
struct Node //数据结点
{
	BitNode* data;  //数据，BitNode结构体类型的指针
	pNode next; //指针
};

struct Stack  //此结构记录栈的大小和栈顶元素指针
{
	pNode top; //栈顶元素指针
	int size; //栈大小
};

LinkStack Create(); //创建栈
int IsEmpty(LinkStack lstack); //判断栈是否为空
int Push(LinkStack lstack, BitNode* val); //元素入栈
pNode getTop(LinkStack lstack); //获取栈顶元素
pNode Pop(LinkStack lstack); //弹出栈顶元素

#endif
