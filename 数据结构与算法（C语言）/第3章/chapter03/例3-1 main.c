#include <stdio.h>
#include <stdlib.h>
#include "seqstack.h"

int main()
{
	srand((unsigned)time(0)); //以时间为种子产生随机
	SeqStack stack; //创建一个顺序栈
	InitStack(&stack); //初始化栈
	
	//向栈中添加元素
	for (int i = 0; i < 50; i++)
	{
		SeqStack_Push(&stack, rand() % 1000); //添加的是随机产生的数
	}

	//获取栈顶元素
	printf("栈顶元素：%d\n", SeqStack_Top(&stack));

	//打印栈中元素
	printf("栈中的元素:");
	for (int i = 0; i < 50; i++)
	{
		if (i % 5 == 0)
			printf("\n"); //每5个元素一行
		printf("%d  ", SeqStack_Pop(&stack));  //依次将栈顶元素弹出	
	}

	printf("\n");

	system("pause");
	return 0;
}
