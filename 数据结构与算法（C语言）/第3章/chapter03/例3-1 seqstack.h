#ifndef _SEQSTACK_H_
#define _SEQSTACK_H_

#define MAXSIZE 1024
#define INFINITY 65535
typedef struct
{
	int data[MAXSIZE]; //在结构中定义一个数组
	int top;  //指示栈顶元素,在数组中相当于索引
}SeqStack;

void InitStack(SeqStack* stack); //初始化栈
int IsEmpty(SeqStack* stack); //判断栈是否为空
int SeqStack_Top(SeqStack* stack); //返回栈顶元素
int SeqStack_Pop(SeqStack* stack); //弹出栈顶元素
void SeqStack_Push(SeqStack* stack, int val); //将元素val压入栈中
void SeqStack_Destory(SeqStack* stack); //销毁栈

#endif
