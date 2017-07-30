#include <stdio.h>
#include <stdlib.h>
#include "LinkQueue.h"

int main()
{
	LQueue Lq = Create();
	srand((unsigned)time(0));
	for (int i = 0; i < 10; i++)
		Insert(Lq, rand() % 100);
	printf("队列长度：%d\n", getLength(Lq));
	printf("队头元素：%d\n", GetHead(Lq));
	printf("队头元素  出队元素\n");
 	while (getLength(Lq) > 0) //出队列，循环条件是队列不为空
 	{
 		int ret = GetHead(Lq);//获取队头元素
 		printf("  %d          ", ret);
 		ret = Del(Lq)->data; //出队列
 		printf("%d\n", ret);
 	}

	Clear(Lq); //清空队列
	system("pause");
	return 0;
}
