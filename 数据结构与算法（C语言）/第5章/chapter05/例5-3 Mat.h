#include <stdio.h>
#include <stdlib.h>

#define ROW 3
#define COL 4
#define Max ((ROW)>(COL)?(ROW):(COL))
typedef int ElemType;
typedef struct MatrixPointer
{
	int row;
	int col;
	struct MatrixPointer *right, *down;
	union
	{
		ElemType value;
		struct MatrixPointer *link;
	}tag;
}MatNode;		//十字链表类型定义
//创建一个十字链表，并使用数组a初始化
void cmatCreate(MatNode *&hm, ElemType a[ROW][COL]);
//输出
void cmatPrint(MatNode *hm);