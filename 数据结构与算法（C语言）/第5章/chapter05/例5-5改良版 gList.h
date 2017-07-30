#include <stdio.h>
#include <stdlib.h>

typedef struct LinkListsNode
{
	int tag;							//标志位
	union
	{
		int data;					//单元素
		struct LinkListsNode *Lists;	//指向子表的指针
	}value;
	struct LinkListsNode *link;			//指向下一个元素
}LSNode;								//广义表结点类型定义
//求广义表的长度
int LSLength(LSNode *ls);
//求广义表的深度
int LSDepth(LSNode *ls);
//输出广义表ls
void LSDis(LSNode *ls);
//广义表创建
void LSCreate(LSNode** ls, int flag);