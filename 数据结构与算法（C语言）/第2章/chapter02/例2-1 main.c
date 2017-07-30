#include "SeqList.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _Teacher
{
	char name[32];
	int age;
}Teacher;

int main()
{
	int ret = 0;
	SeqList * list = NULL;
	Teacher t1, t2, t3, t4, t5; //结点元素
	t1.age = 31;
	t2.age = 32;
	t3.age = 33;
	t4.age = 34;
	t5.age = 35;
	//创建结点
	list = SeqList_Create(10);  //创建顺序表
	
	//插入结点
	ret = SeqList_Insert(list, (SeqListNode*)&t1, 0); //位置0表示始终在头部插入
	ret = SeqList_Insert(list, (SeqListNode*)&t2, 0);
	ret = SeqList_Insert(list, (SeqListNode*)&t3, 0);
	ret = SeqList_Insert(list, (SeqListNode*)&t4, 0);
	ret = SeqList_Insert(list, (SeqListNode*)&t5, 0);

	printf("顺序表容量：%d\n", SeqList_Capacity(list));
	printf("顺序表长度：%d\n", SeqList_Length(list));
	
	//遍历顺序表
	printf("遍历顺序表：\n");
	for (int i = 0; i < SeqList_Length(list); i++)
	{
		Teacher* temp = (Teacher*)SeqList_Get(list, i); //获取链表结点
		if (temp == NULL)
		{
			printf("func SeqList_Get() error\n", ret);
			return;
		}
		
		printf("age: %d\n", temp->age);
	}


	//销毁链表
	printf("销毁顺序表时：\n");
	while (SeqList_Length(list) > 0)
	{
		Teacher* temp = (Teacher *)SeqList_Delete(list, 0); //删除头部元素
		if (temp == NULL)
		{
			printf("func SeqList_Get() error\n", ret);
			return;
		}
		
		printf("age: %d\n", temp->age);
	}
	SeqList_Destory(list);

	system("pause");
	return 0;
}
