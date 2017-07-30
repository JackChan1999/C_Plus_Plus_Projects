#include <stdio.h>
#include <stdlib.h>
#include "SeqQueue.h"

int main()
{
	SeqQueue Sq = Create(); //创建队列
	srand((unsigned)time(0));
	for (int i = 0; i < 10; ++i)
	{
		Insert(Sq, rand() % 100); //入队列，随机产生的数
	}
	printf("队列长度：%d\n", getLength(Sq));
	printf("队头元素  出队元素\n");
	while (Sq->front != Sq->rear) //出队列，循环条件是队列不为空
	{
		int ret = GetHead(Sq);//获取队头元素
		printf("  %d          ", ret);
		ret = Del(Sq); //出队列
		printf("%d\n", ret);
	}
	printf("队列长度：%d\n", getLength(Sq));
	Clear(Sq);
	Destory(Sq);

	system("pause");
	return 0;
}
