#include "seqstack.h"

void InitStack(SeqStack* stack) //初始化栈
{
	stack->top = -1; 
}

int IsEmpty(SeqStack* stack) //判断栈是否为空
{
	if (stack->top == -1)
		return 1;
	return 0;
}

int SeqStack_Top(SeqStack* stack) //返回栈顶元素
{
	if (!IsEmpty(stack))
		return stack->data[stack->top];
	return INFINITY; //只是作个简单标识，有可能栈顶元素也为-1；
}

int SeqStack_Pop(SeqStack* stack) //弹出栈顶元素
{
	if (!IsEmpty(stack))
		return stack->data[stack->top--]; //弹出一个元素后，top要减1
	return INFINITY;
}

void SeqStack_Push(SeqStack* stack, int val) //将元素val压入栈中
{
	if (stack->top >= MAXSIZE - 1) //栈已满
		return;
	stack->top++; //增加元素后，top要加1
	stack->data[stack->top] = val; //将val元素存到数组中
}

void SeqStack_Destory(SeqStack* stack) //销毁栈
{
	if (!IsEmpty(stack))
		free(stack);
}
