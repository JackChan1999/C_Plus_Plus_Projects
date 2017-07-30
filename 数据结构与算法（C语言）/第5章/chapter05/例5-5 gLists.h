#include <stdio.h>
#include <stdlib.h>

//结构体定义
typedef struct LinkListsNode
{
	int tag;							//标志位
	union
	{
		char atom;						//单元素
		struct LinkListsNode *Lists;	//指向子表的指针
	}value;
	struct LinkListsNode *link;			//指向同一层中的后继元素
}LSNode;								//广义表结点类型定义
//广义表的递归创建
void LSCreate(LSNode** ls);
//递归求广义表的深度
int LSDepth(LSNode *ls);
//输出广义表ls
void LSDis(LSNode *ls);
//求广义表的长度
int LSLength(LSNode *ls);