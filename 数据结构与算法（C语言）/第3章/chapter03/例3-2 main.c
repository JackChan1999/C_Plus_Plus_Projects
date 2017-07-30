#include <stdio.h>
#include <stdlib.h>
#include "linkstack.h"

int main()
{
	srand((unsigned)time(0));
	LinkStack lstack = NULL;
	lstack = Create(); //创建一个栈

	//判断栈是否为空
	int ret;
	ret = IsEmpty(lstack);
	if (ret)
		printf("栈为空！\n");
	else
		printf("栈不为空！\n");

	//向栈中插入元素
	for (int i = 0; i < 10; i++)
	{
		Push(lstack, rand() % 100); //插入的是随机产生的数
	}

	//再次判断栈是否为空
	ret = IsEmpty(lstack);
	if (ret)
		printf("栈为空！\n");
	else
		printf("栈不为空！\n");

	//求栈的长度
	printf("栈的长度：%d\n", getSize(lstack));

	//获取栈顶元素
    //返回的是pNode结点类型，要转换为int类型
	printf("栈顶元素：%d\n", *((int*)getTop(lstack))); 

	//打印栈中的元素
	while (lstack->size > 0)
	{
         //Pop()返回的是pnode结点类型，也要转换为int类型
		printf("%d  ", *((int*)Pop(lstack))); 
	}
	printf("\n");

	//销毁栈
	Destory(lstack);

	system("pause");
	return 0;
}
